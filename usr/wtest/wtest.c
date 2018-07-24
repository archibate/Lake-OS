#include <lxL4/sysipc.h>
#include <lxL4/sysmm.h>
#include <lxL4/umemlay.h>
#include <string.h>
#include <malloc.h>

int main(void)
{
#if 0
	static char restxt[20] = "Welcome to lkOS/lxL4";
	//char *data = (char *) malloc(20);
	//static char data[20];
	L4m_Setbrk(USR_STACK_BEG + PGSIZE);
	char *data = (char *) USR_STACK_BEG;
	char *res = (char *) USR_STACK_BEG + 20;
	memcpy(res, restxt, 20);
#else
	static char restxt[20] = "Welcome to lkOS/lxL4";
#endif
again:;
	char *data = (char *) malloc(20);
	char *res = (char *) malloc(20);
	memcpy(res, restxt, 20);
	//printstr("w waiting...\n");
	L4_Wait(5, data);
	//printstr("w got data=");
	//printnstr(data, sizeof(data));
	//printstr("\n");
	//printstr("w replying...\n");
	L4_ReplyWait(5, res, data);
	free(data);
	free(res);
	goto again;
}
