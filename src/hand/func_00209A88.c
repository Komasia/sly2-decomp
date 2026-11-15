/* func_00209A88 (0x209A88): EOPID 278's getter: the guard's state mask as a list of its states, highest first. */
#include "stepguard.h"
struct CRef { int tagk; int tag; };
void *func_00207AA0(long grfState, char *ast);   /* the mask's states */
void func_00200F58(struct CRef *pref, void *cst, int grf, char *ast);   /* makes a list ref */
struct CRef *func_00209A88(struct CRef *pref, struct GUARD *pguard) { char ast[0xC0]; func_00200F58(pref, func_00207AA0(pguard->grfState, ast), 0x1010, ast); return pref; }
