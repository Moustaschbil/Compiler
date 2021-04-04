
.data


.text

main:
    addiu $29, $29, 0
a: .word 0
    lw    $4, 0($29)
    ori   $8, $0, 0x0
    ori   $2, $0, 0xa
    syscall
    lw    $4, 0($29)
a: .word 0
    lw    $4, 0($29)
    ori   $8, $0, 0x0
main:
    addiu $29, $29, 0
a: .word 0
    lw    $4, 0($29)
    ori   $8, $0, 0x0
    ori   $2, $0, 0xa
    syscall
    lw    $4, 0($29)
a: .word 0
    lw    $4, 0($29)
    ori   $8, $0, 0x0
