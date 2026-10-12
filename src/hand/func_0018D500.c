struct S { char pad[0xF04]; int n; };
extern char D_002DE2E0[];
int func_0014FD50(void *p);
int func_0018D500(struct S *p)
{
    int r = 1;
    if (p->n == r) return 0;
    if (func_0014FD50(D_002DE2E0)) r = 0;
    return r;
}
