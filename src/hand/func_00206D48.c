/* func_00206D48 (0x206D48): whether the guard belongs to one of the five special guard families (D_002C3D10:
 * 0x3B, 0x40, 0x3D, 0x3E, 0x41), which don't take part in modes 34 / 37. */
extern int D_002C3D10[];   /* the special guard classes */
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
int func_00206D48(void *pguard) { unsigned int icid; for (icid = 0; icid < 5; icid++) if (FIsBasicDerivedFrom__FP5BASIC3CID(pguard, D_002C3D10[icid])) return 1; return 0; }
