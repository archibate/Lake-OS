#include "reg_t.h"

typedef struct jmp_buf_struct {
	reg_t si, di, bx, bp, sp;
};

int __attribute__((fastcall)) setjmp(jmp_buf env);
void __attribute__((fastcall, noreturn)) longjmp(jmp_buf env, int val);
