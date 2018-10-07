#include "main.h"
#include "circularBuf.h"

unsigned char irStatus;
unsigned char irCnt = 0;
CircularBuffer irInputCB;
int bktIdx = BUCKETS;
unsigned long maxBkt;
unsigned long maxBktVal;
unsigned long freqTickSum = 0;
unsigned long freqCnt = 0;
unsigned long freqBuckets[BUCKETS + 1];

inline void initIR() {
    circularBufInit(&irInputCB);
}

inline void doPrintIR() {
    if (bktIdx >= BUCKETS) {
        bktIdx = 0;
    }
}

inline void printIR(char printed) {
    if (bktIdx == 0) {
        int i;
        maxBkt = 0;
        maxBktVal = 0;
        if (freqCnt != 0) {
            unsigned long a = ldiv(freqTickSum, freqCnt).quot;
            unsigned long f = ldiv(5000000, a).quot;
            printf("Cant %lu Sum %lu AVG %lu FREQ %lu [HZ]\r\n",
                    freqCnt,
                    freqTickSum,
                    a, f);
        }
        printf("\r\n        ");
        for (i = 0; i <= 0xF; i++) {
            printf("%6u ", i);
        }
    }
    if (bktIdx < BUCKETS) {
        if ((bktIdx & 0xF) == 0) {
            printf("\r\n %4u : ", bktIdx);
        }
        if (freqBuckets[bktIdx] > maxBktVal) {
            maxBkt = bktIdx;
            maxBktVal = freqBuckets[bktIdx];
        }
        printf("%6u ", freqBuckets[bktIdx]);
        bktIdx++;
        if (bktIdx >= BUCKETS) {
            printf("\r\n");
            if (maxBkt > 0) {
                unsigned long f = ldiv(5000000, maxBkt).quot;
                printf("maxBkt %lu maxBktVal %lu FREQ %lu [HZ]\r\n",
                        maxBkt,
                        maxBktVal,
                        f);
            }
        }
    }

    if (!printed) {
        if (irStatus != IR_OK) {
            printf("IRE %u\r\n", irStatus);
            irStatus = DH_OK;
        }
    } else {
        if (irStatus == IR_OK) {
            unsigned long data;

            // critiscal section
            INTDisableInterrupts();
            unsigned char t = (circularBufRemove(&irInputCB, &data));
            INTEnableInterrupts();
            if (t) {
                if (data == 0) {
                    printf("\r\n");
                    irCnt = 0;
                }
                if ((irCnt & 0xF) == 0) {
                    printf("\r\n %u : ", irCnt);
                }
                printf("%lu ", data);
                irCnt++;
            }
        }
    }
}

inline void processIrOptoData(unsigned short val) {
    if (val < BUCKETS) {
        mPORTAToggleBits(BIT_10);
        freqTickSum += val;
        freqCnt++;
        freqBuckets[val]++;
    }
}
unsigned char lastPush = 0;

void processIrSensorData(unsigned long val) {
    if (val > MAX_SENSOR_TIME) {
        val = 0;
    }
    if (irStatus == IR_OK) {
        if (!circularBufAdd(&irInputCB, val)) {
            irStatus = IR_ERROR_BUFFER_OVERFLOW;
            mPORTASetBits(BIT_10);
        };
    }
}