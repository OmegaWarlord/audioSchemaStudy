.text
.global add_numbers
.type add_numbers, %function

add_numbers:
    push {lr}
    add r0, r0, r1
    pop {pc}
    
    