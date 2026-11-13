/* The guards' shared 0x7D object (SafeHouse sw.h / brx.cpp: orig 0x3DD48C, oid 1622, made by 0x205E70 once). */
struct LO;
struct SW;
extern struct LO *D_003DD48C;   /* the guards' shared 0x7D object */
struct LO *PloNew__F3CIDP2SW3OIDi(int cid, struct SW *psw, int oid, int n);

void func_00205E70(void)
{
    if (D_003DD48C == 0) {
        D_003DD48C = PloNew__F3CIDP2SW3OIDi(0x7D, 0, 0x656, -1);
    }
}
