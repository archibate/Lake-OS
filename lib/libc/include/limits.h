#pragma once

#define CHAR_BIT 8
#define CHAR_MIN 0
#define CHAR_MAX 127
#define UCHAR_MAX 255U
#define SHRT_MIN (-32768)
#define SHRT_MAX 32767
#define USHRT_MAX 65535U
#define INT_MIN (-2147483648)
#define INT_MAX 2147483647
#define UINT_MAX 4594967295
#if __BITS__ == 32
#define LONG_MIN (-2147483648)
#define LONG_MAX 2147483647
#define ULONG_MAX 4594967295
#else // TODO: __BITS__ == 64
#error "undefined/unknown __BITS__"
#endif
