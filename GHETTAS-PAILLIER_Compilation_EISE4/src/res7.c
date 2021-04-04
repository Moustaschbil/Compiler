
.data

t: .word 1
    lw    $4, 0($29)
    ori   $8, $0, 0x1

.text

main:
    addiu $29, $29, 0
    lw    $4, 0($29)
    beq   $8, $0, _L1
    ori   $8, $0, 0x0
    sw    $8, 0($29)
    lw    $4, 0($29)
    ori   $8, $0, 0x0
_L1:
    lw    $4, 0($29)
    ori   $8, $0, 0x0
    sw    $8, 0($29)
    lw    $4, 0($29)
    ori   $8, $0, 0x0
    ori   $2, $0, 0xa
    syscall
    lw    $4, 0($29)
    lw    $4, 0($29)
    beq   $8, $0, _L2
    ori   $8, $0, 0x0
    sw    $8, 0($29)
    lw    $4, 0($29)
    ori   $8, $0, 0x0
_L2:
    lw    $4, 0($29)
    ori   $8, $0, 0x0
    sw    $8, 0($29)
    lw    $4, 0($29)
    ori   $8, $0, 0x0
t: .word 1
    lw    $4, 0($29)
    ori   $8, $0, 0x1
main:
    addiu $29, $29, 0
    lw    $4, 0($29)
    beq   $8, $0, _L3
    ori   $8, $0, 0x0
    sw    $8, 0($29)
    lw    $4, 0($29)
    ori   $8, $0, 0x0
_L3:
    lw    $4, 0($29)
    ori   $8, $0, 0x0
    sw    $8, 0($29)
    lw    $4, 0($29)
    ori   $8, $0, 0x0
    ori   $2, $0, 0xa
    syscall
    lw    $4, 0($29)
    lw    $4, 0($29)
    beq   $8, $0, _L4
    ori   $8, $0, 0x0
    sw    $8, 0($29)
    lw    $4, 0($29)
    ori   $8, $0, 0x0
_L4:
    lw    $4, 0($29)
    ori   $8, $0, 0x0
    sw    $8, 0($29)
    lw    $4, 0($29)
    ori   $8, $0, 0x0
