OUTPUT_FORMAT("elf32-i386")
ENTRY(_start)

SECTIONS {
        . = 0x8000;
        .start : { *(.start) }
        .text : { *(.text*) }
        .rodata : { *(.rodata*) }
        .data : { *(.data*) }
        .bss : { *(.bss*) }
}
