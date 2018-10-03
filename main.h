/* 
 * File:   main.h
 * Author: adji
 *
 * Created on December 27, 2012, 10:01 AM
 */

#ifndef MAIN_H
#define	MAIN_H
#include <xc.h>
#include <plib.h>

#define False 0
#define True 1


#ifdef	__cplusplus
extern "C" {
#endif

#define SYS_FREQ 		(40000000L)
#define	GetPeripheralClock()		(SYS_FREQ/(1 << OSCCONbits.PBDIV))
#define	GetInstructionClock()		(SYS_FREQ)
//#define BAUDRATEREG2        ((GetPeripheralClock()+(BRG_DIV2/2*BAUDRATE2))/BRG_DIV2/BAUDRATE2-1)
#define BAUDRATE    57600   // serial baudrate

    void usbSerialInit(void);
    void usbSerialService(void);
    void usbSerialPutchar(char ch);
    unsigned int usbSerialGetchar(void);
    unsigned char usbSerialGetLen(void);
    unsigned char isReadyToWrite();

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

