#pragma once

void init_gdtidt(void);
void init_tss(void);
void init_pic(void);
void init_pagging(void);
void init_ppm(void);
void init_timer(unsigned int freq);
void init_tty0(void);
void init_idle(void);
void init_initrdap(void);
