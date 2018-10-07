#include"circularBuf.h"

void circularBufInit(CircularBuffer*buf) {
    buf->head = 0;
    buf->tail = 0;
}

unsigned char circularBufAdd(CircularBuffer*buf, unsigned short data) {
    unsigned short l;
    l = (buf->head + 1) & RBUF_MASK;
    if (l == buf->tail) {
        return 0;
    }
    buf->buf[ buf->head ] = data;
    buf->head = l;
    return 1;
}

unsigned char circularBufRemove(CircularBuffer*buf, unsigned short *data) {
    if (buf->head == buf->tail) {
        return 0;
    }
    *data = buf->buf[ buf->tail ];
    buf->tail++;
    buf->tail = buf->tail & RBUF_MASK; // % cb->size
    return 1;
}
