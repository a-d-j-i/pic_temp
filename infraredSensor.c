#include "main.h"

unsigned char irStatus;
unsigned short bktIdx = FREQ_BUCKETS;
unsigned long maxBkt;
unsigned long maxBktVal;
unsigned long freqTickSum = 0;
unsigned long freqCnt = 0;
unsigned long freqBuckets[FREQ_BUCKETS + 1];

unsigned short timeIdx = TIME_BUCKETS;
unsigned long timeCnt = 0;
unsigned long timeBuckets[TIME_BUCKETS + 1];

inline void initIR() {
}

inline void doPrintIR() {
    if (bktIdx >= FREQ_BUCKETS) {
        bktIdx = 0;
    }
}

inline void doPrintSensor() {
    timeIdx = 0;
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
    if (bktIdx < FREQ_BUCKETS) {
        if ((bktIdx & 0xF) == 0) {
            printf("\r\n %4u : ", bktIdx);
        }
        if (freqBuckets[bktIdx] > maxBktVal) {
            maxBkt = bktIdx;
            maxBktVal = freqBuckets[bktIdx];
        }
        printf("%6lu ", freqBuckets[bktIdx]);
        bktIdx++;
        if (bktIdx >= FREQ_BUCKETS) {
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

    if (timeIdx < TIME_BUCKETS && timeBuckets[timeIdx] != 0) {
        if ((timeIdx & 0xF) == 0) {
            printf("\r\n %4u : ", timeIdx);
        }
        printf("%6lu ", timeBuckets[timeIdx]);
        timeIdx++;
        if (timeIdx >= TIME_BUCKETS) {
            printf("\r\n");
        }
    }
    if (!printed) {
        if (irStatus != IR_OK) {
            printf("IRE %u\r\n", irStatus);
            irStatus = IR_OK;
        }
    }
}

inline void processIrOptoData(unsigned short val) {
    if (val < FREQ_BUCKETS) {
        mPORTAToggleBits(BIT_10);
        freqTickSum += val;
        freqCnt++;
        freqBuckets[val]++;
    }
}
unsigned char lastPush = 0;

void processIrSensorData(unsigned long val) {
    if (irStatus == IR_OK) {
        if (val > MAX_SENSOR_TIME) {
            timeCnt = 0;
        }
        if (timeCnt < TIME_BUCKETS) {
            mPORTAToggleBits(BIT_10);
            timeBuckets[timeCnt] = val;
            if (timeCnt < TIME_BUCKETS - 1) {
                timeBuckets[timeCnt + 1] = 0;
            }
            timeCnt++;
        } else {
            irStatus = IR_ERROR_BUFFER_OVERFLOW;
            mPORTASetBits(BIT_10);
        }
    }
}