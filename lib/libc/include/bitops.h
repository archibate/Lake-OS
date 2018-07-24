#pragma once

#define LOWORD(x) ((x) & 0xffff)
#define HIWORD(x) (((x) >> 16) & 0xffff)
#define LOBYTE(x) ((x) & 0xff)
#define HIBYTE(x) (((x) >> 8) & 0xff)
