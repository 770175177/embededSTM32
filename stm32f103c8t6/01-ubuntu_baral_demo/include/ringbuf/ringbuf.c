#include "ringbuf.h"
#include <string.h>
#include 

void ringbuf_init(struct ringbuf *rb, char *buf, int buf_len)
{
    rb->buf = buf;
    rb->max_len = buf_len;
    rb->tail = 0;
    rb->head = 0;
}

int ringbuf_put(struct ringbuf *rb, char *data, int data_len)
{
    if (ringbuf_remain(rb) <= data_len) {
        memcpy(rb->buf + rb->tail, data, data_len);
    } else {
        
    }
}

int ringbuf_get(struct ringbuf *rb, char **data,  int *data_len)
{

}