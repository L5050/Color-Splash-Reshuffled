/* linker.ld */
INCLUDE @CS_HEADERS_DIR@/linker/us.lst

SECTIONS
{
    .text :
    {
        *(.text*)
    }

    .bss :
    {
        *(.bss*)
        __bss_start = .;
        __bss_end = .;
        __end__ = .;
        _end = .;
    }
}