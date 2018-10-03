#include "main.h"

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_2, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1
#pragma config ICESEL   = ICS_PGx3      // ICE/ICD Comm Channel Select

#pragma config UPLLEN   = ON        // USB PLL Enabled
//#pragma config FPLLMUL  = MUL_15        // PLL Multiplier
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
//#pragma config FPLLIDIV = DIV_2         // PLL Input Divider
//#pragma config FPLLODIV = DIV_1         // PLL Output Divider
//#pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
//#pragma config FWDTEN   = OFF           // Watchdog Timer
#pragma config WDTPS    = PS1           // Watchdog Timer Postscale
#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC = OFF           // CLKO Enable
//#pragma config POSCMOD  = HS            // Primary Oscillator
#pragma config IESO     = OFF           // Internal/External Switch-over
#pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
//#pragma config FNOSC    = PRIPLL        // Oscillator Selection
#pragma config CP       = OFF           // Code Protect
#pragma config BWP      = OFF           // Boot Flash Write Protect
#pragma config PWP      = OFF           // Program Flash Write Protect
//#pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select


//
// when used with a prescaler of 1 usec = 40
// when used with a prescaler of 4 usec = 10
// when used with a prescaler of 8 usec = 5
//T1_PS_1_8 1 tick == 1/5 usec
//T1_PS_1_64 1 tick == 8/5 usec
//T1_PS_1_256 1 tick == 32/5 usec

#define PS_8_USEC 5
#define PS_8_MSEC (1000 * PS_8_USEC)
#define PS_8_SEC (1000 * PS_8_MSEC)

#define PS_16_MSEC (PS_8_MSEC / 2)
#define PS_16_SEC (1000 * PS_16_MSEC);

#define PS_32_MSEC (PS_8_MSEC / 4)
#define PS_32_SEC (1000 * PS_32_MSEC)

#define PS_64_MSEC (PS_8_MSEC / 8)
#define PS_64_SEC (1000 * PS_64_MSEC)

#define PS_256_SEC (125 * 250 * 5)

int _mon_getc(int canblock) {
    int ch;
    ch = usbSerialGetchar();
    if (ch >= 0) {
        return ch;
    }
    return ch;
}

// Redirect stdout

void _mon_putc(char c) {
    usbSerialPutchar(c);
}

enum {
    DH_OK,
    DH_ERROR_BAD_START,
    DH_ERROR_TOO_INVALID_VAL,
    DH_ERROR_TOO_INVALID_CHECKSUM,
    DH_ERROR_TOO_MANY_VALS
} DH_ERROR;
unsigned char dhtStatus = 0;
unsigned char dhtCnt = 0;
unsigned char dhtBytes[6];
unsigned char dhtBytesCnt = 0;
BOOL printed = FALSE;

unsigned short printIdx = 0xFFFF;
unsigned short irCnt = 0;
unsigned long irBuf[1024];

int main(void) {
    int ch = 0;
    int pbClk; // the PB frequency
    // Configure the device for maximum performance but do not change the PBDIV
    // Given the options, this function will change the flash wait states, RAM
    // wait state and enable prefetch cache but will not change the PBDIV.
    // The PBDIV value is already set via the pragma FPBDIV option above..
    pbClk = SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
    //disable JTAG port
    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);

    // LED2, D10, RED ERROR
    mPORTAClearBits(BIT_10);
    mPORTASetPinsDigitalOut(BIT_10);

    // LED1 D13, GREEN
    mPORTBClearBits(BIT_15);
    mPORTBSetPinsDigitalOut(BIT_15);

    // IR LED A0 == RC0
    mPORTCClearBits(BIT_0);
    mPORTCSetPinsDigitalOut(BIT_0);

    // RC5 = D5 == dht11
    mPORTCSetBits(BIT_5);
    mPORTCSetPinsDigitalIn(BIT_5);

    ConfigIntTimer45(T45_INT_ON | T45_INT_PRIOR_3);
    ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_2);
    ConfigIntCapture4(IC_INT_ON | IC_INT_PRIOR_4);
    ConfigIntCapture2(IC_INT_ON | IC_INT_PRIOR_5);


    //mPORTCClearBits(BIT_6);
    //mPORTCSetPinsDigitalOut(BIT_6);

    
    // RPC6 == D6 == IN -> IC1 or IC5
    // RPB1 == A3 ir receiver
    // RPC7 == D7 -> C2OUT
    //mPORTCClearBits(BIT_7);
    //mPORTCSetPinsDigitalOut(BIT_7);
    //CMP2Open(CMP_ENABLE | CMP_OUTPUT_ENABLE | CMP_EVENT_CHANGE | CMP_POS_INPUT_C2IN_POS | CMP2_NEG_INPUT_IVREF);
    //PPSOutput(1, RPC7, C2OUT);


    //CMP2ConfigInt(CMP_INT_ENABLE|CMP_INT_PRIOR_5);
    //INTClearFlag(INT_CMP2);

    /*ConfigIntOC1(OC_INT_ON | OC_INT_PRIOR_8)
    OpenOC1(OC_ON | OC_IDLE_STOP | OC_TIMER_MODE32 |
            OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE | OC_SINGLE_PULSE, 0x0000, 0xFFFF);
     */

    // two seconds tick, can be done with 23 too.
    OpenTimer45(T45_ON | T45_SOURCE_INT | T45_PS_1_256, 2 * PS_256_SEC);

    // 18ms for dht to start measuring.
    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_64, 18 * PS_64_MSEC);

    // fast timer used for input capture
    OpenTimer23(T23_ON | T23_SOURCE_INT | T23_PS_1_8, 0xFFFFFFFF);

    OpenCapture4(IC_ON | IC_SP_EVERY_EDGE | IC_FEDGE_FALL | IC_TIMER2_SRC | IC_INT_1CAPTURE | IC_CAP_16BIT);
    PPSInput(1, IC4, RPC5);

    OpenCapture2(IC_ON | IC_SP_EVERY_EDGE | IC_FEDGE_FALL | IC_TIMER2_SRC | IC_INT_1CAPTURE | IC_CAP_32BIT);
    PPSInput(4, IC2, RPC4);

    usbSerialInit();
    while (1) {
        if (!printed) {
            printed = TRUE;
            if (dhtStatus == DH_OK) {
                printf("Temp: %u.%u [C]\r\n", dhtBytes[2], dhtBytes[3]);
                printf("Humidity: %u.%u [%%]\r\n", dhtBytes[0], dhtBytes[1]);
            } else {
                printf("ERROR %u CNT %u BYTES CNT: %u\r\n", dhtStatus, dhtCnt, dhtBytesCnt);
            }
            printf("\r\n");
        }
        if (printIdx < irCnt) {
            printf("%u %lu  ", printIdx, irBuf[printIdx]);
            if ((printIdx & 0xF) == 0xF) {
                printf("\r\n");
            }
            printIdx++;
            if (printIdx == irCnt) {
                //irCnt = 0;
                printIdx = 0xFFFF;
                printf("\r\n");
            }
        }
        ch = _mon_getc(False);
        if (ch > 0) {
            switch (ch) {
                case 13:
                case ' ':
                    printf("\r\n");
                    break;
                case 'p':
                case 'P':
                    printIdx = 0;
                    break;
                case 'x':
                case 'X':
                    printf("%u\r\n", mPORTCReadBits(BIT_0));
                    mPORTCSetBits(BIT_0);
                    printf("%u\r\n", mPORTCReadBits(BIT_0));
                    break;
                case 'c':
                case 'C':
                    irCnt = 0;
                    break;
                case 'l':
                case 'L':
                    dhtStatus = DH_OK;
                    break;
                case 'h':
                case 'H':
                    printf("Usage: [x/X] toggle ir, [l/L] clear dht errpr, [p/P] print \r\n");
                    break;
                default:
                    break;
            }
        }
        usbSerialService();
    }
}

inline void setError(unsigned char err) {
    dhtStatus = err;
    mPORTASetBits(BIT_10);
}

void __ISR(_TIMER_45_VECTOR, IPL3SOFT) Timer45Handler(void) {
    if (mT45GetIntFlag()) {
        printed = FALSE;
        // turn off ir
        mPORTCClearBits(BIT_0);
        // toggle green
        mPORTBToggleBits(BIT_15);
        if (dhtStatus == DH_OK) {

            mPORTAClearBits(BIT_10);
            dhtCnt = 0;
            dhtBytesCnt = 0;
            WriteTimer1(0);
            WriteTimer23(0);
            mPORTCSetPinsDigitalOut(BIT_5);
            mPORTCClearBits(BIT_5);
            T1CONbits.TON = 1;
        }
        mT45ClearIntFlag();
    }
}

void __ISR(_TIMER_1_VECTOR, IPL2SOFT) Timer1Handler(void) {
    if (mT1GetIntFlag()) {
        mPORTCSetBits(BIT_5);
        mPORTCSetPinsDigitalIn(BIT_5);
        T1CONbits.TON = 0;
        mT1ClearIntFlag();
    }
}

unsigned short dhtLastCapture;

void __ISR(_INPUT_CAPTURE_4_VECTOR, IPL4SOFT) InputCapture4_Handler(void) {
    if (mIC4GetIntFlag()) {
        if (mIC4CaptureReady()) {
            unsigned short c = mIC4ReadCapture();
            unsigned short val = c - dhtLastCapture;
            dhtLastCapture = c;
            if (dhtCnt < 100) {
                if (dhtStatus == DH_OK) {
                    if (dhtCnt >= 0 && dhtCnt < 3) {
                    } else if (dhtCnt == 3 || dhtCnt == 4) {
                        if (val < 400 || val > 450) {
                            setError(DH_ERROR_BAD_START);
                        }
                    } else if (dhtCnt > 4 && dhtCnt <= 86) {
                        if ((dhtCnt & 1) == 0) {
                            if (val > 400 || val < 100) {
                                setError(DH_ERROR_TOO_INVALID_VAL);
                            } else {
                                unsigned char idx = (dhtBytesCnt >> 3);
                                if (val < 235) {
                                    // zero
                                    dhtBytes[idx] = dhtBytes[idx] << 1;
                                } else {
                                    // one
                                    dhtBytes[idx] = (dhtBytes[idx] << 1) | 1;
                                }
                                dhtBytesCnt++;
                            }
                        }
                        if (dhtCnt == 86) {
                            unsigned char ch = dhtBytes[0] + dhtBytes[1] + dhtBytes[2] + dhtBytes[3];
                            if (ch != dhtBytes[4]) {
                                setError(DH_ERROR_TOO_INVALID_CHECKSUM);
                            }
                        }
                    } else {
                        setError(DH_ERROR_TOO_MANY_VALS);
                    }
                }
                dhtCnt++;
            }
        }
        mIC4ClearIntFlag();
    }
}

unsigned long irLastCapture;

void __ISR(_INPUT_CAPTURE_2_VECTOR, IPL5SOFT) InputCapture2_Handler(void) {
    if (mIC2GetIntFlag()) {
        if (mIC2CaptureReady()) {
            unsigned long c = mIC2ReadCapture();
            unsigned long val = c - irLastCapture;
            irLastCapture = c;
            if (irCnt < 1000) {
                irBuf[irCnt] = val;
                irCnt++;
            }
        }
        mIC2ClearIntFlag();
    }
}
