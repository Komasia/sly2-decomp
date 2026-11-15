/* JOBSCRIPT::PloNear: the object of an oid seen from the job's near object (or anywhere without one). */
struct JOBSCRIPT { char pad[0x34]; int ploNear; };
struct SW { int a; };
extern struct SW g_sw;
void *PloFindSwNearest__FP2LO3OIDii(struct SW *psw, int grf, int oid, int ploCtx);
// name: SafeHouse port (JOBSCRIPT::PloNear)
void *PloNear__9JOBSCRIPT3OID(struct JOBSCRIPT *pjob, int oid) { int ploNear = pjob->ploNear; int grf = ploNear ? 4 : 5; return PloFindSwNearest__FP2LO3OIDii(&g_sw, grf, oid, ploNear); }
