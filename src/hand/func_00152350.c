/* class: CID_44, the dancers (vt slot 50 = the pose definition; SafeHouse actor.cpp: the base's definition with its
 * heading turned by -3 pi / 4). */
struct SO;
struct CPDEFI {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ float radHeading;
};
void GetSoCpdefi__FP2SOP6CPDEFI(struct SO *pso, struct CPDEFI *pcpdefi);

void func_00152350(struct SO *pso, struct CPDEFI *pcpdefi)
{
    GetSoCpdefi__FP2SOP6CPDEFI(pso, pcpdefi);
    pcpdefi->radHeading -= 2.3561945f;
}
