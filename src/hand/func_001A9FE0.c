struct O { char pad[0xAC]; struct O *next; };
void func_001A9FE0(void *unused, struct O *b, struct O **pp)
{
    if (b) {
        struct O *last = b;
        while (last->next) last = last->next;
        last->next = *pp;
        *pp = b;
    }
}
