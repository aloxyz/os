#pragma once

#include "types.h"

#define VIDEO_RAM (char *)0xb8000
#define VIDEO_X 80
#define VIDEO_Y 25

#define COL_DEFAULT 0x07
#define COL_FG_RED 0x04
#define COL_FG_BLUE 0x31

static inline void outb(unsigned short port, unsigned char val);

void vga_cur_off();

void cls(int x, int y);

void prts(cursor *cur, const char *str, int color);

void prtc(cursor *cur, unsigned char c, unsigned int color);

