#include "tty.h"
#include "asm.h"
#include "clicrit.h"
#include "string.h"

typedef unsigned short buf_offset_t;

static void __tty_putchar(struct tty_ctl *tty, tty_char_t ch);
static void __tty_putchar_d(struct tty_ctl *tty, tty_char_t ch);
static void __tty_newline(struct tty_ctl *tty);
static void tty_putdata(struct tty_ctl *tty, tty_data_t data);
static void tty_scrollup(struct tty_ctl *tty);
static void tty_update_cursor(struct tty_ctl *tty);
static void tty_download_cursor(struct tty_ctl *tty);
static void termio_set_cursor(buf_offset_t cur);
static buf_offset_t termio_get_cursor(void);

int tty_init(struct tty_ctl *tty,
		tty_data_t *buf, int nx, int ny)
{
	CLI_CRIT_BEGIN(1);
	tty->buf = buf;
	tty->nx = nx;
	tty->ny = ny;
	tty->bgcolor = 0x0700;
	tty->fgcolor = 0x0700;
	tty->esc = 0;
	tty->esc_type = 0;
	tty_download_cursor(tty);
	CLI_CRIT_END(1);
}

void tty_putstr(struct tty_ctl *tty, const char *s)
{
	char ch;
	CLI_CRIT_BEGIN(1);
	while ((ch = *s++)) {
		__tty_putchar(tty, ch);
	}
	tty_update_cursor(tty);
	CLI_CRIT_END(1);
}

void tty_putnstr(struct tty_ctl *tty, const char *s, unsigned n)
{
	CLI_CRIT_BEGIN(1);
	while (n--) {
		__tty_putchar(tty, *s++);
	}
	tty_update_cursor(tty);
	CLI_CRIT_END(1);
}

void tty_putchar(struct tty_ctl *tty, char ch)
{
	CLI_CRIT_BEGIN(1);
	__tty_putchar(tty, ch);
	tty_update_cursor(tty);
	CLI_CRIT_END(1);
}

void tty_putchar_d(struct tty_ctl *tty, char ch)
{
	CLI_CRIT_BEGIN(1);
	__tty_putchar_d(tty, ch);
	tty_update_cursor(tty);
	CLI_CRIT_END(1);
}

void __tty_putchar(struct tty_ctl *tty, tty_char_t ch)
{
	if (tty->esc) {
		if (tty->esc_type) {
			switch (tty->esc_type) {
			case 'c':
				tty->fgcolor = ch << 8;
				break;
			}
			tty->esc = 0;
		} else if (ch == 'c') {
			tty->esc_type = ch;
		} else {
			__tty_putchar_d(tty, '\033');
			__tty_putchar_d(tty, ch);
		}
	} else if (ch == '\n') {
		tty_newline(tty);
	} else if (ch == '\r') {
		tty->x = 0;
	} else if (ch == '\b') {
		if (tty->x > 0)
			tty->x--;
	} else if (ch == '\033') {
		tty->esc = 1;
		tty->esc_type = 0;
	} else {
		__tty_putchar_d(tty, ch);
	}
}
static void __tty_putchar_d(struct tty_ctl *tty, tty_char_t ch)
{
	tty_putdata(tty, tty->fgcolor | ch);
}

static void tty_putdata(struct tty_ctl *tty, tty_data_t data)
{
	buf_offset_t offset = tty->y * tty->nx + tty->x;
	tty->buf[offset] = data;
	if (++tty->x >= tty->nx) {
		tty_newline(tty);
	}
}

void tty_clear(struct tty_ctl *tty)
{
	CLI_CRIT_BEGIN(1);
	for (int i = 0; i < tty->ny * tty->nx; i++) {
		tty->buf[i] = tty->bgcolor;
	}
	tty->x = 0;
	tty->y = 0;
	tty_update_cursor(tty);
	CLI_CRIT_END(1);
}

void tty_newline(struct tty_ctl *tty)
{
	CLI_CRIT_BEGIN(1);
	__tty_newline(tty);
	tty_update_cursor(tty);
	CLI_CRIT_END(1);
}

static void __tty_newline(struct tty_ctl *tty)
{
	tty->x = 0;
	if (tty->y + 1 >= tty->ny) {
		tty_scrollup(tty);
	} else {
		tty->y++;
	}
}

static void tty_scrollup(struct tty_ctl *tty)
{
	int scsize = tty->nx * (tty->ny - 1);
	memcpy(tty->buf, tty->buf + tty->nx, scsize * sizeof(tty->buf[0]));
	for (int i = 0; i < tty->nx; i++) {
		tty->buf[scsize + i] = tty->bgcolor;
	}
}

static void tty_update_cursor(struct tty_ctl *tty)
{
	buf_offset_t cur = tty->y * tty->nx + tty->x;
	termio_set_cursor(cur);
}

static void tty_download_cursor(struct tty_ctl *tty)
{
	buf_offset_t cur = termio_get_cursor();
	tty->y = cur / tty->nx;
	tty->x = cur % tty->nx;
}

static void termio_set_cursor(buf_offset_t cur)
{
	unsigned char lo = cur & 0xff,
		      hi = (cur >> 8) & 0xff;
	io_outb(0x3d4, 0x0e);
	io_outb(0x3d5, hi);
	io_outb(0x3d4, 0x0f);
	io_outb(0x3d5, lo);
}

static buf_offset_t termio_get_cursor(void)
{
	io_outb(0x3d4, 0x0e);
	unsigned char hi = io_inb(0x3d5);
	io_outb(0x3d4, 0x0f);
	unsigned char lo = io_inb(0x3d5);
	buf_offset_t cur = (hi << 8) | lo;
	return cur;
}
