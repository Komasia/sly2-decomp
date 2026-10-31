/* __builtin_new (0x1AE4F8, Sly 1 memory.c): g++'s operator new - a zeroed allocation from the world heap. Sly 2's
 * allocators take a request {size, alignment} (the symbol keeps Sly 1's PvAllocSwClearImpl(int) mangling). */
typedef struct ALLOCREQ {
    int cb;         /* bytes */
    int cbAlign;    /* alignment */
} ALLOCREQ;

void *PvAllocSwClearImpl__Fi(ALLOCREQ *pallocreq);

void *__builtin_new(int cb)
{
    ALLOCREQ allocreq;

    allocreq.cb = cb;
    allocreq.cbAlign = 0x10;
    return PvAllocSwClearImpl__Fi(&allocreq);
}
