/* 
 * File:   circularBuffer.h
 * Author: adji
 *
 * Created on October 6, 2018, 7:05 AM
 */

#ifndef CIRCULARBUFFER_H
#define	CIRCULARBUFFER_H

#ifdef	__cplusplus
extern "C" {
#endif
    // The page has 256 bytes, so I'm using 128 for the receive buffer.
    // Because 128 is 2^7 I can do the modulus operation as an and so this is the chosen size.
    // For the send buffer I choose 2^6=64, so I have some byte in the same page for other variables.
#define RBUF_MASK (0x3FF)

    typedef struct {
        unsigned long head;
        unsigned long tail;
        unsigned short buf[ RBUF_MASK + 1 ];
    } CircularBuffer;


    void circularBufInit(CircularBuffer*buf);
    unsigned char circularBufAdd(CircularBuffer*buf, unsigned short data);
    unsigned char circularBufRemove(CircularBuffer*buf, unsigned short *data);

#ifdef	__cplusplus
}
#endif

#endif	/* CIRCULARBUFFER_H */

