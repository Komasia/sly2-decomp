struct S { char pad[0x13D0]; int k; };
void ApplyAloGravity__FP3ALO(struct S *p);
void UpdateStepPhysMotion__FP3ALO(struct S *p);
void UpdateJumpMotion__FP4JUMP(void *p);
void func_00194170(void *p);
void UpdateDamageMotion__FP5ACTOR(void *p);
void UpdateMurrayFlopMotion__FP6MURRAY(struct S *p);
void UpdateClimbMotion__FP5ACTOR(void *p);
// name: SafeHouse port (UpdateMurrayMotion)
void UpdateMurrayMotion__FP3ALO(struct S *p)
{
    char *b = (char *)p;
    if (p->k == 20) ApplyAloGravity__FP3ALO(p);
    else UpdateStepPhysMotion__FP3ALO(p);
    switch (p->k) {
    case 2: UpdateJumpMotion__FP4JUMP(b + 0x2C0); break;
    case 13: func_00194170(b + 0x4C0); break;
    case 14: UpdateDamageMotion__FP5ACTOR(b + 0xDF0); break;
    case 3: UpdateMurrayFlopMotion__FP6MURRAY(p); break;
    case 20: UpdateClimbMotion__FP5ACTOR(b + 0xF50); break;
    }
}
