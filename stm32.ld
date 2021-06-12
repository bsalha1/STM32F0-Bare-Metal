ENTRY(reset)

MEMORY {
    flash (RX) : ORIGIN = 0x08000000, LENGTH = 256K
    sram (!RX) : ORIGIN = 0x20000000, LENGTH = 32K
}

SECTIONS {
    .vectors : { *(.vectors) } >flash
    .text : { *(.text) } >flash
    .rodata : { *(.rodata) } >flash
    .bss : { *(.bss) } >sram
}