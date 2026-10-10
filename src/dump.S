.global _dump_reg

_dump_reg:
    b _dump_loop

_dump_end:
    ret

_dump_loop:
    add x0, x0, #1
    sub x1, x1, #1
    cmp x1, #0
    beq _dump_end
    bne _dump_loop