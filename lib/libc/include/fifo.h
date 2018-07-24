#pragma once

typedef unsigned int fifo_data_t;
typedef unsigned char fifo_index_t;

struct fifo256 {
	fifo_data_t buf[256];
	fifo_index_t w, r;
};

static inline int fifo256_empty(struct fifo256 *fifo)
{
	return fifo->w == fifo->r;
}

static inline void fifo256_put(struct fifo256 *fifo, fifo_data_t data)
{
	fifo->buf[fifo->w++] = data;
}

static inline fifo_data_t fifo256_get(struct fifo256 *fifo)
{
	return fifo->buf[fifo->r++];
}
