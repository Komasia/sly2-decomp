/* func_00205E70 (0x205E70): makes the guards' shared 0x7D object (oid 1622) once (SafeHouse sw.h / brx.cpp: orig
 * 0x3DD48C). */
struct LO;
struct SW;
extern struct LO *D_003DD48C;   /* the guards' shared 0x7D object */
struct LO *PloNew__F3CIDP2SW3OIDi(int cid, struct SW *psw, int oid, int n);

#define CID_GUARDSHARED 0x7D
#define OID_GUARDSHARED 0x656

void func_00205E70(void)
{
    if (D_003DD48C == 0) {
        D_003DD48C = PloNew__F3CIDP2SW3OIDi(CID_GUARDSHARED, 0, OID_GUARDSHARED, -1);
    }
}
