#include "video.h"

static inline void outb(unsigned short port, unsigned char val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void vga_cur_off() {
    // Disable cursor by setting bit 5 (0x20) in Cursor Start/End regs
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
    outb(0x3D4, 0x0B);
    outb(0x3D5, 0x20);
}

void cls(int x, int y) {
        char *video = VIDEO_RAM;

        for(int i = 0; i < x*y; i++) {
                *video++ = ' ';
                *video++ = 0x07;
        }
}

void prts(cursor *cur, const char *str, int color) {
        while (*str) {
                prtc(cur, *str++, color);
                cur->x++;
        }
}

void prtc(cursor *cur, unsigned char c, unsigned int color) {
        char *video = VIDEO_RAM;

        int pos = 2 * (cur->y * VIDEO_X + cur->x);
        if (cur->x < VIDEO_X && cur->y < VIDEO_Y) {
                video[pos] = c;
                video[pos+1] = color;
        }
}

