// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
typedef int word_type;
#define FIRST_PSEUDO_REGISTER 79
typedef struct frame_state {
    void *cfa;
    void *eh_ptr;
    long cfa_offset;
    long args_size;
    long reg_or_offset[FIRST_PSEUDO_REGISTER + 1];
    unsigned short cfa_reg;
    unsigned short retaddr_column;
    char saved[FIRST_PSEUDO_REGISTER + 1];
} frame_state;

enum { REG_UNSAVED, REG_SAVED_OFFSET, REG_SAVED_REG };

extern void abort(void) __attribute__((noreturn));

static __inline__ int in_reg_window(int reg, frame_state *udata) { return 0; }

word_type *get_reg_addr(unsigned reg, frame_state *udata, frame_state *sub_udata)
{
    while (udata->saved[reg] == REG_SAVED_REG)
    {
        reg = udata->reg_or_offset[reg];
        if (in_reg_window(reg, udata))
        {
            udata = sub_udata;
            sub_udata = 0;
        }
    }
    if (udata->saved[reg] == REG_SAVED_OFFSET)
        return (word_type *)((char *)udata->cfa + udata->reg_or_offset[reg]);
    else
        abort();
}
