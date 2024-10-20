#include "ringbuf.h"

void ringbuf_init(struct ringbuf *rb, char *buf, int buf_len)
{
    rb->buf = buf;
    rb->max_len = buf_len;
    rb->tail = 0;
    rb->head = 0;
}

int ringbuf_put(struct ringbuf *rb, char *data, int data_len)
{
    if (ringbuf_remain <= data_len) {

    } else {
        
    }
}

int ringbuf_get(struct ringbuf *rb, char **data,  int *data_len)
{

}