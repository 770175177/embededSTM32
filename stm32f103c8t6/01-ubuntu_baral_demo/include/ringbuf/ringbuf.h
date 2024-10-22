#ifndef __RING_BUF_H__
#define	__RING_BUF_H__

typedef struct ringbuf {
    unsigned char *buf;
    int max_len;
    int tail;
    int head;
} ringbuf;

#define ringbuf_is_empty(_buf)  (_buf->tail == _buf->head)
#define ringbuf_is_full(_buf)   (_buf->_buf->tail + 1 == _buf->head)
#define ringbuf_remain(_buf)    ((_buf->head + _buf->max_len - _buf->tail) % _buf->max_len - 1)
#define ringbuf_len(_buf)       ((_buf->tail + _buf->max_len - _buf->head) % _buf->max_len)
#define ringbuf_len(_buf)       (_buf->max_len - _buf->tail)

void ringbuf_init(struct ringbuf *rb, char *buf, int buf_len)
#define ringbuf_put(_buf)
#define ringbuf_get(_buf)

#endif /* __RING_BUF_H__ */