struct S { int k; char pad[0x50]; void *o; };
int FSpriteAnimPlaying__FP2LOi(void *o, int a);
void SetWipeState__FPv5WIPES(struct S *p, int k);
// name: SafeHouse port (UpdateWipe)
void UpdateWipe__FP4WIPE(struct S *p)
{
    int k = p->k;
    switch (k) {
    case 0: break;
    case 1: if (!FSpriteAnimPlaying__FP2LOi(p->o, 0x314)) k = 3; break;
    case 2: if (!FSpriteAnimPlaying__FP2LOi(p->o, 0x314)) k = 0; break;
    }
    SetWipeState__FPv5WIPES(p, k);
}
