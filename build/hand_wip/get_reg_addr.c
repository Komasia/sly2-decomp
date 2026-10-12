// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
__asm__(".macro sq r, m\n\tsd \\r, \\m\n\t.endm\n\t.macro lq r, m\n\tld \\r, \\m\n\t.endm");
#include "/tmp/claude-0/-home-claude/c373c316-8d22-5589-afaf-2023f6177e2b/scratchpad/z23c/fs.h"
word_type *get_reg_addr(unsigned reg, frame_state *udata, frame_state *sub_udata)
{
  char *saved = udata->saved;
  while (saved[reg] == REG_SAVED_REG)
    reg = udata->reg_or_offset[reg];
  if (saved[reg] == REG_SAVED_OFFSET)
    return (word_type *)(udata->cfa + udata->reg_or_offset[reg]);
  else
    abort();
}
