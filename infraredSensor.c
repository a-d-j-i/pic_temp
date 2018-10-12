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
unsigned short timeBuckets[TIME_BUCKETS + 1];

unsigned char run = FALSE;
unsigned short runIdx = 0;

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
        printf("%6u ", timeBuckets[timeIdx]);
        timeIdx++;
        if (timeIdx >= TIME_BUCKETS) {
            printf("\r\n");
        }
    }
    if (!printed) {
        printf("FREQ: %u, run %u\r\n", getMaxBkt(), run);
        if (irStatus != IR_OK) {
            printf("IRE %u\r\n", irStatus);
            irStatus = IR_OK;
        }
    }
}

inline unsigned short getMaxBkt() {
    unsigned short i;
    unsigned long maxVal = 0;
    unsigned short maxBkt = 0;
    for (i = 0; i < FREQ_BUCKETS; i++) {
        if (freqBuckets[i] > maxVal) {
            maxBkt = i;
            maxVal = freqBuckets[i];
        }
    }
    return maxBkt;

    //return 124;
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
    if (!run) {
        if (irStatus == IR_OK) {
            if (val > MAX_SENSOR_TIME) {
                timeCnt = 0;
            }
            if (timeCnt < TIME_BUCKETS) {
                mPORTAToggleBits(BIT_10);
                timeBuckets[timeCnt] = (unsigned short) val;
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
}

inline void setFreq(unsigned short period) {
    OC1CONCLR = _OC1CON_ON_MASK;
    TMR3 = 0;
    PR3 = period;
    // half on / half off.
    OC1R = (period >> 1);
}

inline void irDoRun() {
    runIdx = 1;
    run = TRUE;
    // set timer period
    if (timeBuckets[runIdx] != 0) {
        printf("RUN at freq %u\r\n", getMaxBkt());
        // turn on oscilator
        OC1CONSET = _OC1CON_ON_MASK;
        // turn run timer
        //OpenTimer5(T5_ON | T5_SOURCE_INT | T5_PS_1_8, timeBuckets[runIdx++]);
        T5CONCLR = _T5CON_ON_MASK;
        TMR5 = 0;
        PR5 = timeBuckets[runIdx++];
        T5CONSET = _T5CON_ON_MASK;
    }
}

inline void runTime() {
    if (run && runIdx < TIME_BUCKETS && timeBuckets[runIdx] != 0) {
        mPORTBToggleBits(BIT_15);
        OC1CONINV = _OC1CON_ON_MASK;
        T5CONCLR = _T5CON_ON_MASK;
        TMR5 = 0;
        PR5 = timeBuckets[runIdx++];
        T5CONSET = _T5CON_ON_MASK;
    } else {
        OC1CONCLR = _OC1CON_ON_MASK;
        T5CONCLR = _T5CON_ON_MASK;
        TMR5 = 0;
        run = FALSE;
    }
}
