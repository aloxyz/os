[bits 16]
[org 0x7c00]

jmp 0x0000:start

; ENTRY POINT

start:
        cli             ; Disable hardware interrupts
        xor ax, ax      
        mov ds, ax
        mov es, ax

        mov si, loading_msg
        call print_string

        ; Load sector 2 from disk to memory at 0000:8000
        mov ah, 0x02    ; BIOS read sectors function
        mov al, 4       ; # of sectors to read
        mov ch, 0       ; cylinder
        mov cl, 2       ; Read second sector, first sector is the bootloader
        mov dh, 0       ; head
        mov dl, 0x80    ; drive, first disk
        mov bx, 0x8000  ; Address where to store read data
        int 0x13        ; Read sector in memory, BIOS interrupt

        ; PROTECTED MODE
        cli
        lgdt [gdt_descriptor]   ; Load GDTR

        mov eax, cr0
        or eax, 1               ; PE bit in CR0
        mov cr0, eax            ; Enable protected mode

        jmp 0x08:protected_entry

; ROUTINES

[bits 32]
protected_entry:
        mov ax, 0x10            ; Data selector
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax
        mov esp, 0x90000        ; Prepare 32-bit stack at 0x90000

        jmp 0x08:0x8000         ; Jump to kernel

        cli
        hlt

[bits 16]

print_string:
        mov ah, 0x0e    ; BIOS Teletype output
.next:
        lodsb
        cmp al, 0
        je .done
        int 0x10
        jmp .next
.done:
        ret

gdt_start:
        dq 0x0000000000000000
        dq 0x00CF9A000000FFFF
        dq 0x00CF92000000FFFF

gdt_end:

gdt_descriptor:
        dw gdt_end - gdt_start - 1
        dd gdt_start

; DATA

loading_msg db "Loading kernel...", 0

; BOOT SECTOR SIGNATURE

times 510 - ($-$$) db 0
dw 0xAA55
