// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
typedef unsigned int uword;
typedef int sword;
typedef struct dwarf_fde {
    uword length;
    sword CIE_delta;
    void *pc_begin;
    uword pc_range;
} fde;

static __inline__ fde *next_fde(fde *p)
{
    return (fde *)((char *)p + p->length + sizeof(p->length));
}

unsigned int count_fdes(fde *this_fde)
{
    unsigned int count;
    uword len;

    for (count = 0; (len = this_fde->length) != 0; this_fde = (fde *)((char *)this_fde + len + sizeof(this_fde->length)))
    {
        if (this_fde->CIE_delta != 0 && this_fde->pc_begin != 0)
            ++count;
    }
    return count;
}
