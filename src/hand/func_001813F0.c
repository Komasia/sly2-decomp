/* class: CID_49, the hack enemies (SafeHouse hack.cpp, EOPID 1377: the push gain +0x384 = 5 (D_002BE87C) x r). */
struct ENEMY {
    /* 0x000 */ char pad0[0x384];
    /* 0x384 */ float gPush;   /* field: SafeHouse port - the push gain */
};
extern float D_002BE87C;   /* 5.0f */

void func_001813F0(struct ENEMY *penemy, float r)
{
    penemy->gPush = r * D_002BE87C;
}
