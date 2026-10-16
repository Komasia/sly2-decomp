// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
int strcmp(const char *, const char *);
void *__throw_type_match(void *catch_type, void *throw_type, void *obj)
{
    if (strcmp((const char *)catch_type, (const char *)throw_type) == 0)
        return obj;
    return 0;
}
