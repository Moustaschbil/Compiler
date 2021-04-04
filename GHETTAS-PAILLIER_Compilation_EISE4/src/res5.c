
.data


.text

main:
    addiu $29, $29, 0
c: .word 2
    lw    $4, 0($29)
    ori   $8, $0, 0x2
    lw    $8, 0($29)
    ori   $8, $0, 0x0
    div   $8, $8
    mflo  $8
    lw    $4, 0($29)
    ori   $8, $0, 0x0
    sw    $8, 0($29)
    lw    $4, 0($29)
    lw    $8, 0($29)
    ori   $8, $0, 0x0
    div   $8, $8
    mflo  $8
    lw    $4, 0($29)
    ori   $8, $0, 0x0
    ori   $2, $0, 0xa
    syscall
    lw    $4, 0($29)
c: .word 2
    lw    $4, 0($29)
    ori   $8, $0, 0x2
    lw    $8, 0($29)
    ori   $8, $0, 0x0
    div   $8, $8
    mflo  $8
    lw    $4, 0($29)
    ori   $8, $0, 0x0
    sw    $8, 0($29)
    lw    $4, 0($29)
    lw    $8, 0($29)
    ori   $8, $0, 0x0
    div   $8, $8
    mflo  $8
    lw    $4, 0($29)
    ori   $8, $0, 0x0
main:
    addiu $29, $29, 0
c: .word 2
    lw    $4, 0($29)
    ori   $8, $0, 0x2
    lw    $8, 0($29)
    ori   $8, $0, 0x0
    div   $8, $8
    mflo  $8
    lw    $4, 0($29)
    ori   $8, $0, 0x0
    sw    $8, 0($29)
    lw    $4, 0($29)
    lw    $8, 0($29)
    ori   $8, $0, 0x0
    div   $8, $8
    mflo  $8
    lw    $4, 0($29)
    ori   $8, $0, 0x0
    ori   $2, $0, 0xa
    syscall
    lw    $4, 0($29)
c: .word 2
    lw    $4, 0($29)
    ori   $8, $0, 0x2
    lw    $8, 0($29)
    ori   $8, $0, 0x0
    div   $8, $8
    mflo  $8
    lw    $4, 0($29)
    ori   $8, $0, 0x0
    sw    $8, 0($29)
    lw    $4, 0($29)
    lw    $8, 0($29)
    ori   $8, $0, 0x0
    div   $8, $8
    mflo  $8
    lw    $4, 0($29)
    ori   $8, $0, 0x0
