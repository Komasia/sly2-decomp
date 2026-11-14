/* class: an object with a flag at +0x1AC set by two load-option descriptors (0x2B4BF8 / 0x2B4C00): the flag is
 * the option's value negated. */
typedef struct LO1AC {
    /* 0x000 */ char pad0[0x1ac];
    /* 0x1ac */ int fOff;
} LO1AC;

void func_001C3C08(LO1AC *plo, int fOn)
{
    plo->fOff = (fOn == 0);
}
