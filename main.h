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

    enum {
        DH_OK,
        DH_READING,
        DH_ERROR_BAD_START,
        DH_ERROR_INVALID_ST_VAL,
        DH_ERROR_INVALID_DT_VAL,
        DH_ERROR_INVALID_VAL,
        DH_ERROR_INVALID_CHECKSUM,
        DH_ERROR_TOO_MANY_VALS
    } DH_ERROR;
#define MAX_DHT_IDX 90

    void doPrintDhtData();
    char dhtStart();
    void printDHT(char printed);
    void processDHT(unsigned short val);

    enum {
        IR_OK,
        IR_ERROR_BUFFER_OVERFLOW,
    } IR_ERROR;

// 50ms 0x3FFFF == 262143 == 52428.6usec
#define MAX_SENSOR_TIME 0x3FFFF

#define FREQ_BUCKETS 511
#define TIME_BUCKETS 511
    void initIR();
    void doPrintIR();
    void doPrintSensor();
    void printIR(char printed);
    void processIrOptoData(unsigned short val);
    void processIrSensorData(unsigned long val);

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

