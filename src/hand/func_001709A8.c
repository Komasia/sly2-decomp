/* func_001709A8: the kind of a path object for the guards: 0 a CID_PATH_0D, 1 a pipe, -1 any other path. */
#include "cid.h"
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
int func_001709A8(void *ppath) { if (FIsBasicDerivedFrom__FP5BASIC3CID(ppath, CID_PATH_0D)) return 0; if (FIsBasicDerivedFrom__FP5BASIC3CID(ppath, CID_PIPE)) return 1; return -1; }
