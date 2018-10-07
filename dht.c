#include "main.h"
unsigned short dhtIdx = MAX_DHT_IDX;

unsigned char dhtStatus = 0;
unsigned char dhtCnt = 0;
unsigned short dhtVal[MAX_DHT_IDX + 1];
unsigned char dhtBytes[6];
unsigned char dhtBytesCnt = 0;

inline void doPrintDhtData() {
    if (dhtIdx >= dhtCnt) {
        dhtIdx = 0;
    }
}

inline void printDHT(char printed) {
    if (dhtIdx < dhtCnt) {
        if ((dhtIdx & 0xF) == 0) {
            printf("\r\n %u : ", dhtIdx);
        }
        printf("%u ", dhtVal[dhtIdx++]);
        if (dhtIdx == dhtCnt) {
            printf("\r\n");
        }
    }
    if (!printed) {
        if (dhtStatus != DH_READING) {
            if (dhtStatus != DH_OK) {
                printf("DHT Error %u\r\n", dhtStatus);
                mPORTAClearBits(BIT_10);
                dhtStatus = DH_OK;
            } else {
                printf("T: %u.%u [C]\r\n", dhtBytes[2], dhtBytes[3]);
                printf("H: %u.%u [%%]\r\n", dhtBytes[0], dhtBytes[1]);
            }
            printf("\r\n");
        }
    }
}

inline void setError(unsigned char err) {
    dhtStatus = err;
    mPORTASetBits(BIT_10);
}

inline char dhtStart() {
    if (dhtStatus == DH_OK) {
        dhtCnt = 0;
        dhtBytesCnt = 0;
        return 1;
    }
    return 0;
}

inline void processDHTBit(unsigned char dhtCnt, unsigned short val) {
    if (dhtCnt == 0 || dhtCnt == 1|| dhtCnt == 2) {
        return;
    }

    if (dhtCnt == 3 || dhtCnt == 4) {
        if (val < 400 || val > 450) {
            setError(DH_ERROR_BAD_START);
        }
        return;
    }

    if (dhtCnt >= 86) {
        setError(DH_ERROR_TOO_MANY_VALS);
        return;
    }

    // 4 - 84
    if (val > 400 || val < 100) {
        setError(DH_ERROR_INVALID_VAL);
        return;
    }

    if ((dhtCnt & 1) != 0) {
        if (val < 250 || val > 300) {
            setError(DH_ERROR_INVALID_ST_VAL);
        }
        return;
    }

    unsigned char idx = (dhtBytesCnt >> 3);
    if (val < 150) {
        // zero
        dhtBytes[idx] = dhtBytes[idx] << 1;
    } else if (val > 300) {
        // one
        dhtBytes[idx] = (dhtBytes[idx] << 1) | 1;
    } else {
        setError(DH_ERROR_INVALID_DT_VAL);
        return;
    }
    dhtBytesCnt++;

    if (dhtCnt == 84) {
        unsigned char ch = dhtBytes[0] + dhtBytes[1] + dhtBytes[2] + dhtBytes[3];
        if (ch != dhtBytes[4]) {
            setError(DH_ERROR_INVALID_CHECKSUM);
            return;
        }
    }

}

inline void processDHT(unsigned short val) {
    if (dhtStatus != DH_OK) {
        return;
    }
    if (dhtCnt < MAX_DHT_IDX) {
        dhtVal[dhtCnt] = val;
        processDHTBit(dhtCnt, val);
        dhtCnt++;
    }
}
