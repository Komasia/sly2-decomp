/* func_00170B60: append an op-1 command (a range: its 8 bytes at +0x8). */
struct RANGE { int n0, n4; };
struct CMD { int op, oid; struct RANGE range; };
struct CMD *PcmdAppend__FP7CMDLISTi3OID(void *pcmdlist, int op, int oid);
void func_00170B60(void *pcmdlist, struct RANGE *prange) { PcmdAppend__FP7CMDLISTi3OID(pcmdlist, 1, -1)->range = *prange; }
