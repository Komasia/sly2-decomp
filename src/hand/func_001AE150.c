/* class: the memory manager (Sly 1 memmgr): the free memory between the world's end and the stack's bottom. */
extern char *s_pvWorldMac;
extern char *s_pvStackMin;

int func_001AE150(void)
{
    return s_pvStackMin - s_pvWorldMac;
}
