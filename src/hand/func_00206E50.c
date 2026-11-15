/* func_00206E50 (0x206E50): leaving guard mode 34 / 37: the special guard classes (D_002C3D10) are no longer
 * excluded target classes (0x208948). */
extern int D_002C3D10[];   /* the special guard classes */
void func_00208948(void *pguard, int cid);   /* removes an excluded target class */
void func_00206E50(void *pguard) { unsigned int icid; for (icid = 0; icid < 5; icid++) func_00208948(pguard, D_002C3D10[icid]); }
