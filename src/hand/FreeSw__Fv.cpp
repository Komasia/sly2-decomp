/* FreeSw (Sly 1 memory.c): release everything allocated from the world heap. */
extern void *s_pvWorldMin;
extern void *s_pvWorldMac;

void FreeSw()
{
    s_pvWorldMac = s_pvWorldMin;
}
