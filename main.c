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

unsigned char printed = FALSE;

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

    //ConfigIntOC1(OC_INT_ON | IC_INT_PRIOR_6);
    // RPC6 == D6 == IN -> IC1 or IC5
    // A3 == RPB1 ir transistor receiver
    // RPC7 == D7 -> C2OUT
    //mPORTCClearBits(BIT_7);
    //mPORTCSetPinsDigitalOut(BIT_7);
    //CMP2ConfigInt(CMP_INT_ENABLE|CMP_INT_PRIOR_5);
    //INTClearFlag(INT_CMP2);


    // priority levels range from 1 (lowest) to 7 (highest).
    // 28ms for dht
    ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_5);
    // input capture timer
    ConfigIntTimer2(T2_INT_ON | T2_INT_PRIOR_6);
    // output compare timer
    ConfigIntTimer3(T3_INT_OFF);
    // 2 secs blink
    ConfigIntTimer45(T45_INT_ON | T45_INT_PRIOR_1);

    ConfigIntCapture2(IC_INT_ON | IC_INT_PRIOR_2);
    ConfigIntCapture4(IC_INT_ON | IC_INT_PRIOR_3);
    ConfigIntCapture5(IC_INT_ON | IC_INT_PRIOR_4);
    ConfigIntOC1(OC_INT_OFF);

    // 18ms for dht to start measuring.
    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_64, 18 * PS_64_MSEC);
    // fast timer used for input capture
    OpenTimer2(T23_ON | T2_SOURCE_INT | T2_PS_1_8, 0xFFFF);
    // output compare timer (managed by hardware).
    OpenTimer3(T23_ON | T3_SOURCE_INT | T3_PS_1_8, 0xFFFF);
    // two seconds tick, can be done with 23 too.
    OpenTimer45(T45_ON | T45_SOURCE_INT | T45_PS_1_256, 2 * PS_256_SEC);


    CMP2Open(CMP_ENABLE | CMP_OUTPUT_ENABLE | CMP_EVENT_CHANGE | CMP_POS_INPUT_C2IN_POS | CMP2_NEG_INPUT_IVREF);
    PPSOutput(1, RPC7, C2OUT);

    // D6 == RPC6 output of the comparator
    OpenCapture5(IC_ON | IC_EVERY_FALL_EDGE | IC_FEDGE_FALL | IC_TIMER2_SRC | IC_INT_1CAPTURE | IC_CAP_16BIT);
    PPSInput(3, IC5, RPC6);


    // D5 == dht
    OpenCapture4(IC_ON | IC_SP_EVERY_EDGE | IC_FEDGE_FALL | IC_TIMER2_SRC | IC_INT_1CAPTURE | IC_CAP_16BIT);
    PPSInput(1, IC4, RPC5);

    // D4 ir receiver
    OpenCapture2(IC_ON | IC_SP_EVERY_EDGE | IC_FEDGE_FALL | IC_TIMER2_SRC | IC_INT_1CAPTURE | IC_CAP_16BIT);
    PPSInput(4, IC2, RPC4);


    // starts low, then at value1 goes high, then at value2 goes low and resets the timer.
    //OpenOC1(OC_ON | OC_TIMER_MODE16 | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE | OC_CONTINUE_PULSE, 25, 50);
    //PPSOutput(1, RPC0, OC1);

    initIR();
    // enable priority 1 interrupt
    usbSerialInit();
    while (1) {
        ch = _mon_getc(False);
        if (ch > 0) {
            switch (ch) {
                case 13:
                case ' ':
                    printf("\r\n");
                    break;
                case 'b':
                case 'B':
                    doPrintIR();
                    break;
                case 'd':
                case 'D':
                    doPrintDhtData();
                    break;
                case 'p':
                case 'P':
                    printed = FALSE;
                    break;
                case 'h':
                case 'H':
                    printf("Usage [b]ucket [d]ht [p]rint\r\n");
                    break;
                default:
                    break;
            }
        }
        printIR(printed);
        printDHT(printed);
        if (!printed) {
            printed = TRUE;
        }
        usbSerialService();
    }
}

void __ISR(_TIMER_45_VECTOR, ipl1) Timer45Handler(void) {
    if (mT45GetIntFlag()) {
        printed = FALSE;
        // toggle green
        mPORTBToggleBits(BIT_15);

        /*if (irToggle) {
            OpenOC1(OC_ON | OC_TIMER_MODE32 | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE | OC_CONTINUE_PULSE, 25, 50);
        } else {
            CloseOC1();
        }
        irToggle = !irToggle;
         */
        if (dhtStart()) {
            mPORTAClearBits(BIT_10);
            WriteTimer1(0);
            mPORTCSetPinsDigitalOut(BIT_5);
            mPORTCClearBits(BIT_5);
            T1CONbits.TON = 1;
        }
        mT45ClearIntFlag();
    }
}

void __ISR(_TIMER_1_VECTOR, ipl5) Timer1Handler(void) {
    if (mT1GetIntFlag()) {
        mPORTCSetBits(BIT_5);
        mPORTCSetPinsDigitalIn(BIT_5);
        T1CONbits.TON = 0;
        mT1ClearIntFlag();
    }
}

 unsigned char timer2Capture2RollOver = 0;
unsigned char timer2Capture5RollOver = 0;

void __ISR(_TIMER_2_VECTOR, ipl6) Timer2Handler(void) {
    if (mT2GetIntFlag()) {
        timer2Capture2RollOver = (timer2Capture2RollOver++) & 0x7F;
        timer2Capture5RollOver = (timer2Capture5RollOver++) & 0x7F;
        mT2ClearIntFlag();
    }
}

inline unsigned short getVal(unsigned short c, unsigned short last) {
    if (c < last) {
        return (0xFFFF - last) +c;
    }
    return c - last;
}

void __ISR(_INPUT_CAPTURE_4_VECTOR, ipl3) InputCapture4_Handler(void) {
    static unsigned short dhtLastCapture;
    if (mIC4GetIntFlag()) {
        if (mIC4CaptureReady()) {
            unsigned short c = mIC4ReadCapture();
            unsigned short val = getVal(c, dhtLastCapture);
            dhtLastCapture = c;
            processDHT(val);
        }
        mIC4ClearIntFlag();
    }
}

void __ISR(_INPUT_CAPTURE_2_VECTOR, ipl2) InputCapture2_Handler(void) {
    static unsigned long irLastCapture;
    if (mIC2GetIntFlag()) {
        if (mIC2CaptureReady()) {
            unsigned short c = mIC2ReadCapture();
            unsigned short val;
            if (timer2Capture2RollOver < 2) {
                val = getVal(c, irLastCapture);
                irLastCapture = c;
            } else {
                val = 0;
            }
            timer2Capture2RollOver = 0;
            processIrSensorData(val);
        }
        mIC2ClearIntFlag();
    }
}

void __ISR(_INPUT_CAPTURE_5_VECTOR, ipl4) InputCapture5_Handler(void) {
    static unsigned long freqLastCapture;
    if (mIC5GetIntFlag()) {
        if (mIC5CaptureReady()) {
            unsigned short c = mIC5ReadCapture();
            if (timer2Capture5RollOver < 2) {
                unsigned short val = getVal(c, freqLastCapture);
                freqLastCapture = c;
                processIrOptoData(val);
            }
            timer2Capture5RollOver = 0;
        }
        mIC5ClearIntFlag();
    }
}

void __ISR(_OUTPUT_COMPARE_1_VECTOR, IPL6SOFT) InputCompare1_Handler(void) {
    if (mOC1GetIntFlag()) {
        // turn off ir
        //mPORTCClearBits(BIT_0);
        mOC1ClearIntFlag();
    }
}

