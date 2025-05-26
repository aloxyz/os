#include "video.h"

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

