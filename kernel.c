#include "types.h"
#include "video.h"
#include "kbd.h"

int buffer_pos;

void shell(cursor *cur) {
        char buf[MAX_INPUT]; 
        
        // int by = cur->y;

        int bx = cur->x;

        while(1) {
                prts(cur, "> ", COL_DEFAULT);
                scans(buf, cur);
                cur->y++;
                cur->x = bx;
                prts(cur, buf, COL_FG_BLUE);
                cur->x = bx;
                cur->y++;
        }
}

__attribute__((section(".start")))
void _start() {
        cls(80, 25);
        vga_cur_off();

        cursor cur = { .x =25 , .y = 5 };
        prts(&cur, "ALOS - Alo Operating System", COL_FG_BLUE);

        cur.x = 5;
        cur.y = 10;
        shell(&cur);
        
        while(1);
}
