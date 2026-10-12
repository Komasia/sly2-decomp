struct B { int a; void *p; };
int func_00132B10(void *p, int k);
int func_0020F948(void *a, struct B *b);
int func_0021FB18(void *a, struct B *b)
{
    if (func_00132B10(b->p, 0x59))
        return 1;
    return func_0020F948(a, b);
}
