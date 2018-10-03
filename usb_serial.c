#include "main.h"
#include "./USB/usb.h"
#include "HardwareProfile.h"
#include "./USB/usb_function_cdc.h"

static char outBuffer[CDC_DATA_OUT_EP_SIZE];
static BYTE outLen = 0;
static char inData[CDC_DATA_IN_EP_SIZE];
static BYTE inLen = 0;
static BYTE inCnt = 0;

//USB_HANDLE lastTransmission = 0;

void usbSerialInit(void) {
    USBDeviceInit(); //usb_device.c.  Initializes USB module SFRs and firmware
#if defined(USB_INTERRUPT)
    USBDeviceAttach();
#endif
    //    Called in USBDeviceAttach
    //    configure for multi-vectored mode
    //    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    //    INTEnableInterrupts();

}

void usbSerialService(void) {
#if defined(USB_POLLING)
    USBDeviceTasks(); // Interrupt or polling method.  If using polling, must call
#endif
    // User Application USB tasks
    if ((USBDeviceState < CONFIGURED_STATE) || (USBSuspendControl == 1)) {
        return;
    }
    //usbLen = getsUSBUSART(RS232_Out_Data, 64); //until the buffer is free.
    //Check if any bytes are waiting in the queue to send to the USB host.
    //If any bytes are waiting, and the endpoint is available, prepare to
    //send the USB packet to the host.
    if (USBUSARTIsTxTrfReady() && (outLen > 0)) {
        putUSBUSART(&outBuffer[0], outLen);
        outLen = 0;
    }
    CDCTxService();
}

unsigned char isReadyToWrite() {
    return ( USBUSARTIsTxTrfReady() && outLen == 0 );
}
void usbSerialPutchar(char ch) {
    if (outLen < (CDC_DATA_OUT_EP_SIZE - 1)) {
        outBuffer[ outLen++ ] = ch;
    }
}

unsigned int usbSerialGetchar(void) {

    if (usbSerialGetLen() == 0) {
        return -1;
    }
    inLen--;
    return inData[ inCnt++ ];
}

unsigned char usbSerialGetLen(void) {
    if ((USBDeviceState < CONFIGURED_STATE) || (USBSuspendControl == 1)) {
        return 0;
    }
    if (inLen == 0) {
        inLen = getsUSBUSART(inData, CDC_DATA_IN_EP_SIZE); //until the buffer is free.
        inCnt = 0;
    }
    return inLen;
}

