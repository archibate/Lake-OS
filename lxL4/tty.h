#pragma once

typedef unsigned short tty_data_t;
typedef unsigned char tty_char_t;

struct tty_ctl {
	tty_data_t *buf; // buffer (vram)
	int nx, ny; // size
	int x, y; // cursor

	tty_data_t bgcolor; // background color
	tty_data_t fgcolor; // foreground color

	int esc; // escaped?
	int esc_type; // escape type
};

int tty_init(struct tty_ctl *tty,
		tty_data_t *buf, int nx, int ny);
void tty_putstr(struct tty_ctl *tty, const char *s);
void tty_putnstr(struct tty_ctl *tty, const char *s, unsigned n);
void tty_putchar(struct tty_ctl *tty, char ch);
void tty_putchar_d(struct tty_ctl *tty, char ch);
void tty_clear(struct tty_ctl *tty);
void tty_newline(struct tty_ctl *tty);
