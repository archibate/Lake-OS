#include <sys/cthread.h>
#include <sys/uthread.h>
#include <debug.h>
#include <panic.h>
#include <sysipc.h>
#include <sysmm.h>
#include <mm/vsctl.h>
#include <init/rdap/initrdap.h>

static tcb_t a_thr, b_thr, c_thr;
static char a_stack[1024], b_stack[1024], c_stack[1024];

#define SP(stk) ((reg_t)(stk) + sizeof(stk))

static void w_thread(void)
{
	static char data[20], res[20] = "Welcome to my lwL4!";
	for (;;) L4_Yield();
again:
	//printstr("w waiting...\n");
	L4_Wait(5, data);
	//printstr("w got data=");
	//printnstr(data, sizeof(data));
	//printstr("\n");
	//printstr("w replying...\n");
	L4_ReplyWait(5, res, data);
	goto again;
}

static void a_thread(void)
{
again:
	printstr("a calling w...\n");
	int res = L4_Call1(1, 0x3);
	printstr("a got res=");
	printint(res);
	printstr("\n");
	L4_Call1(0, 0xcafe);
	goto again;
	for (;;); panic("aa");
}

static void b_thread(void)
{
again:
	printstr("b calling w...\n");
	int res = L4_Call1(1, 0x4);
	printstr("b got res=");
	printint(res);
	printstr("\n");
	L4_Call1(0, 0xcafe);
	goto again;
	for (;;); panic("bb");
}

static void c_thread(void)
{
again:
	printstr("c calling w...\n");
	static char res[20], data[20] = "L4oskrnl.sys!";
	L4_Call(5, 1, res, data);
	printstr("c got res=");
	printnstr(res, sizeof(res));
	printstr("\n");
	L4m_Pagger(2, 0, 0x60000000, 0x60000200); // !
	L4m_Pagger(2, 1, 0x80000000, 0x90000000); // !
	//(*(volatile int*)0x60000000) = 12;
	/*int x = (*(volatile int*)0x60000030);
	int y = (*(volatile int*)0x80000020);
	printstr("c got x=");
	printint(x);
	printstr(", y=");
	printint(y);*/
	printstr("\nc got dat:\n=====\n");
	static char dat[512];
	memset(dat, 0, sizeof(dat));
	memcpy(dat, (char*)0x60000000, sizeof(dat));
	printnstr(dat, sizeof(dat));
	/*memset(dat, 0, sizeof(dat));
	memcpy(dat, (char*)0x60000000, sizeof(dat));*/
	printstr("\n=====\n");
	L4_Call1(0, 0xcafe);
	goto again;
	for (;;); panic("cc");
}

void do_test(void)
{
	thread_setup(&a_thr, (reg_t) a_thread, SP(a_stack));
	thread_setup(&b_thr, (reg_t) b_thread, SP(b_stack));
	thread_setup(&c_thr, (reg_t) c_thread, SP(c_stack));
	initrd_thrs[INITRD_APPS-1].next = &a_thr;
	a_thr.next = &b_thr;
	b_thr.next = &c_thr;
	c_thr.next = &initrd_thrs[0];

	CAP_TCB(&a_thr, 1) = &initrd_thrs[0];//ipc server /usr/wtest
	CAP_TCB(&b_thr, 1) = &initrd_thrs[0];//ipc server /usr/wtest
	CAP_TCB(&c_thr, 1) = &initrd_thrs[0];//ipc server /usr/wtest
	CAP_TCB(&a_thr, 0) = &idle_thr;//ipc server idle
	CAP_TCB(&b_thr, 0) = &idle_thr;//ipc server idle
	CAP_TCB(&c_thr, 0) = &idle_thr;//ipc server idle
	CAP_TCB(&c_thr, 2) = &initrd_thrs[5];//fault server /dev/ata

	thread_switch(&initrd_thrs[4]);//fault server /dev/fd0
	ad_t vir = 0x80000000, phy = 0x100000;
	printstr("/dev/fd0: server mem v_map to fd0mem...");
	for (int i = 0; i < 0x168; i++) {
		/*printstr("v_map(vir=");
		printint(vir);
		printstr(", phy=");
		printint(phy);
		printstr(")\n");*/
		v_map(vir, phy, PG_W | PG_U);
		vir += PGSIZE;
		phy += PGSIZE;
	}
	printstr("done\n");
	/*printstr("/svr/fat: set mem server (cid 2) to /dev/fd0\n");
	CAP_TCB(&initrd_thrs[5], 2) = &initrd_thrs[4];//fault server /dev/fd0*/
	thread_switch(&initrd_thrs[5]);//fault server /dev/ata
}
