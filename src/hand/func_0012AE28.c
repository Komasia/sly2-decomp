/* func_0012AE28 (0x12AE28; called by 0x1FF830 when the world is unloaded): the Splice state reset - D_002DD5B8
 * cleared, the six resets 0x257E88..0x257FC8, and five slot heaps emptied (0x11CDB8). */
#include "slotheap.h"

extern int D_002DD5B8;
extern SLOTHEAP D_00452188;
extern SLOTHEAP D_004521A0;
extern SLOTHEAP D_004521B8;
extern SLOTHEAP D_004521D0;
extern SLOTHEAP D_004521E8;
void func_00257E88(void);
void func_00257EC8(void);
void func_00257F08(void);
void func_00257F48(void);
void func_00257F88(void);
void func_00257FC8(void);
void func_0011CDB8(SLOTHEAP *pslotheap);

void func_0012AE28(void)
{
    D_002DD5B8 = 0;
    func_00257E88();
    func_00257EC8();
    func_00257F08();
    func_00257F48();
    func_00257F88();
    func_00257FC8();
    func_0011CDB8(&D_00452188);
    func_0011CDB8(&D_004521A0);
    func_0011CDB8(&D_004521B8);
    func_0011CDB8(&D_004521D0);
    func_0011CDB8(&D_004521E8);
}
