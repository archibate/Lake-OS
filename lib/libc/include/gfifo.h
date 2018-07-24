#pragma once

#define _DEF_FIFO_CLASS(FIFO, DATATYPE) \
typedef DATATYPE FIFO##_data_t; \
typedef unsigned char FIFO##_index_t; \
 \
struct FIFO { \
	FIFO##_data_t buf[256]; \
	FIFO##_index_t w, r; \
}; \
 \
static inline int FIFO##_empty(struct FIFO *fifo) \
{ \
	return fifo->w == fifo->r; \
} \
 \
static inline void FIFO##_put(struct FIFO *fifo, FIFO##_data_t data) \
{ \
	fifo->buf[fifo->w++] = data; \
} \
 \
static inline FIFO##_data_t FIFO##_get(struct FIFO *fifo) \
{ \
	return fifo->buf[fifo->r++]; \
}
