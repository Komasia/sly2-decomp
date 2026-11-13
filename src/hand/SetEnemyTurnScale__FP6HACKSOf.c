/* SetEnemyTurnScale: an enemy's turn rates (+0x378) are the defaults D_002BE870 {25, 0, 0.25} times r, but the
 * third is not scaled. SafeHouse port (hack.cpp: "0x1813C0: +0x378 = D_002BE870 {25, 0, 0.25} x r but +0x380
 * unscaled"). */
struct VECTOR3 { float x, y, z; };
struct HACKSO {
    /* 0x000 */ char pad0[0x378];
    /* 0x378 */ struct VECTOR3 vTurn;
};
extern struct VECTOR3 D_002BE870;   /* {25, 0, 0.25} */

// name: SafeHouse port (SetEnemyTurnScale)
void SetEnemyTurnScale__FP6HACKSOf(struct HACKSO *phackso, float r)
{
    phackso->vTurn.x = D_002BE870.x * r;
    phackso->vTurn.y = D_002BE870.y * r;
    phackso->vTurn.z = D_002BE870.z;
}
