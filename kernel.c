#include "types.h"
#include "video.h"
#include "kbd.h"

int buffer_pos;

void shell(cursor *cur) {
        const char *prefix = "> ";

        for (int i = 0; prefix[i]; i++) {
                prtc(cur, prefix[i], COL_DEFAULT);
        }
}

void bufrw(cursor *cur) {
        char buf[MAX_INPUT];
                prts(cur, "> ", COL_DEFAULT);

        while (1) {
                kbdread(cur, buf);
                prts(cur, buf, COL_FG_RED);
        }
}

__attribute__((section(".start")))
void _start() {
        cls(80, 25);

        cursor cur = { .x =25 , .y = 5 };
        prts(&cur, "ALOS - Alo Operating System", COL_FG_BLUE);


        cur.x = 5;
        cur.y = 10;
        bufrw(&cur);

}
