/* linker.ld */
INCLUDE @CS_HEADERS_DIR@/linker/us.lst

SECTIONS
{
    .text :
    {
        *(.text*)
    }
}
