.global _dump_reg

_dump_reg:
    mov x2, x0
    b _dump_loop

_dump_end:
    ret

_dump_loop:
    ldrb w0, [x2], #1
    cbz w0, _dump_end
    b _dump_loop