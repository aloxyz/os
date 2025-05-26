#pragma once

#include "types.h"

#define KBD_SCAN_PORT 0x60
#define KBD_STATUS_PORT 0x64
#define KBD_BREAK_CODE 0x80

unsigned char read_sc();

char sc2char(unsigned char sc);

int kbd_has_data();

static inline unsigned char inb(unsigned short port);

void kbdread(cursor *cur, char *buf);
