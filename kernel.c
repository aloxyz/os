#define VIDEO_RAM (char *)0xb8000
#define VIDEO_X 80
#define VIDEO_Y 25

#define KBD_SCAN_PORT 0x60
#define KBD_STATUS_PORT 0x64
#define KBD_BREAK_CODE 0x80


#define COL_DEFAULT 0x07
#define COL_FG_RED 0x04

typedef struct {
        int x;
        int y;
} cursor;

void printxy(int x, int y, char c, int col);
int kbd_has_data();

char sc2a(unsigned char sc) {
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

static inline unsigned char inb(unsigned short port) {
        unsigned char ret;
        __asm__ volatile ("inb %1, %0"
                        : "=a"(ret)
                        : "Nd"(port));
        return ret;
}

unsigned char readsc() {
        // Read scancode from keyboard
        while (!kbd_has_data());

        return inb(KBD_SCAN_PORT);
}


int kbd_has_data() {
        return inb(KBD_STATUS_PORT) & 1;
}

void pollsc (cursor *cur) {
        unsigned char sc = readsc();

        if (sc & KBD_BREAK_CODE) {
                return;
        }

        char c = sc2a(sc);
        if (c != 0) {
                printxy(cur->x, cur->y, c, COL_FG_RED);
                cur->x++;
        }
}

void printxy(int x, int y, char c, int col) {
        char *video = VIDEO_RAM;
        int pos = 2 * (y * VIDEO_X + x);

        if (x < VIDEO_X && y < VIDEO_Y) {
                video[pos] = c;
                video[pos+1] = col;
        }
}

void print(const char *str) {
        char *video = VIDEO_RAM;

        while (*str) {
                *video++ = *str++;
                *video++ = 0x31;
        }
}

void clear_screen(int x, int y) {
        char *video = VIDEO_RAM;

        for(int i = 0; i < x*y; i++) {
                *video++ = ' ';
                *video++ = 0x07;
        }
}

__attribute__((section(".start")))
void _start() {
        cursor cur = { .x = 0, .y = 1 };

        clear_screen(80, 25);
        print("Ciao dal kernel!");
        printxy(20, 20, 'x', 0x04);


        while(1) {
                pollsc(&cur);
        }
}
