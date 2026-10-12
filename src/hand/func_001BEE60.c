struct S { char pad[0xE0]; int c; char *a[1]; };
void func_00169198(void *p, struct S *ps);
void func_001BEE60(struct S *p)
{
    int i;
    if (*(int *)((char *)p + 0x128)) {
        for (i = 0; i < p->c; i++) func_00169198(p->a[i] + 0x80, p);
    }
}
