#include "kbd.h"
#include "types.h"
#include "video.h"

unsigned char getsc() {
        // Get scancode from keyboard
        while (!kbd_has_data());
        return inb(KBD_SCAN_PORT);
}

char sc2char(unsigned char sc) {
        // Solo i tasti a-z e 0-9 base
        static const char table[128] = {
                0,  27, '1','2','3','4','5','6','7','8', // 0x00 - 0x09
                '9','0','-','=','\b','\t','q','w','e','r', // 0x0A - 0x13
                't','y','u','i','o','p','[',']','\n', 0, // 0x14 - 0x1D (0=control)
                'a','s','d','f','g','h','j','k','l',';', // 0x1E - 0x27
                '\'', '`', 0, '\\','z','x','c','v','b','n', // 0x28 - 0x31
                'm',',','.','/', 0, '*', 0, ' ', 0, 0,   // 0x32 - 0x3B
                                                         // resto 0
        };

        if (sc > 127) return 0;
        return table[sc];
}

int kbd_has_data() {
        return inb(KBD_STATUS_PORT) & 1;
}

static inline unsigned char inb(unsigned short port) {
        unsigned char ret;
        __asm__ volatile ("inb %1, %0"
                        : "=a"(ret)
                        : "Nd"(port));
        return ret;
}

char readc() {
        // Return keyboard char input
        unsigned char sc = getsc();

        if (sc & KBD_BREAK_CODE) return 0;
        return sc2char(sc);       
}

void scans(char *buf, cursor *cur) {
        // Scan input onto buf until c is newline
        char c = 0;

        while((c = readc()) != '\n') {
                if(c != 0) {
                        *buf++ = c;
                        prtc(cur, c, COL_FG_RED);
                        cur->x++;
                }

        }
        *buf = '\0';
}
