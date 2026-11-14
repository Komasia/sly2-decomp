/* class: a cylindrical object of radius +0x10C (a descriptor at 0x2D2524; its neighbours 0x1834D0 / 0x183540 turn a
 * position into the angle times the radius and back): the parameter's range, -pi to pi times the radius. */
typedef struct LM { float gMin, gMax; } LM;
typedef struct CYL {
    /* 0x000 */ char pad0[0x10c];
    /* 0x10c */ float sRadius;
} CYL;

int func_00183498(CYL *pcyl, LM *plm)
{
    plm->gMin = pcyl->sRadius * -3.1415927f;
    plm->gMax = pcyl->sRadius * 3.1415927f;
    return 1;
}
