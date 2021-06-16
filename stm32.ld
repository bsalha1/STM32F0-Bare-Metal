MEMORY {
    flash (rx) : ORIGIN = 0x08000000, LENGTH = 256K
    sram (!rx) : ORIGIN = 0x20000000, LENGTH = 32K
    system_memory (!r!w!x) : ORIGIN = 0x1FFFD800, LENGTH = 8K 
    option_bytes (!r!w!x) : ORIGIN = 0x1FFFF800, LENGTH = 2K
}

SECTIONS {
    .vectors : { *(.vectors) } >flash
    .text : { *(.text) } >flash
    .rodata : { *(.rodata) } >flash
    .bss : { *(.bss) } >sram
}