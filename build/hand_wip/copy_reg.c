// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
__asm__(".macro sq r, m\n\tsd \\r, \\m\n\t.endm\n\t.macro lq r, m\n\tld \\r, \\m\n\t.endm");
#include "/tmp/claude-0/-home-claude/c373c316-8d22-5589-afaf-2023f6177e2b/scratchpad/z23c/fs.h"
word_type *get_reg_addr(unsigned reg, frame_state *udata, frame_state *sub_udata);
void *func_0023320C(void *, const void *, unsigned long);
static inline int dwarf_reg_size(int reg) { return reg < 31 ? 16 : reg < 64 ? 4 : 8; }
void copy_reg(unsigned reg, frame_state *udata, frame_state *target_udata)
{
  word_type *preg = get_reg_addr(reg, udata, 0);
  word_type *ptreg = get_reg_addr(reg, target_udata, 0);
  func_0023320C(ptreg, preg, dwarf_reg_size(reg));
}
