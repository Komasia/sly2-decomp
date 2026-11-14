/* An option setter (data-referenced): a new +0x204 flag, with +0x208 cleared when it turns on. */
struct LO204 {
    /* 0x000 */ char pad0[0x204];
    /* 0x204 */ int f204;
    /* 0x208 */ int n208;
};

void func_00203FA0(struct LO204 *plo, int f)
{
    if (plo->f204 != f) {
        plo->f204 = f;
        if (f != 0) {
            plo->n208 = 0;
        }
    }
}
