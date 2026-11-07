struct E { int n; int pad[2]; int nC; };
struct P { char pad[0x404]; struct E ae[8]; int c484; int i488; int pad2[2]; void *p494; };
struct G;
extern struct G g_game;
void BroadcastTaskEvent__FP2SWiP2LO(struct G *, int, struct P *);
void *PloLaunchReward__FP2LOi(void *, int);
void SetPocketMode__FP2LOi(struct P *, int);
void NextPocketPrize__FP2LO(struct P *);
// name: SafeHouse port (PloTakePocket)
void *PloTakePocket__FP2LO(struct P *p)
{
    void *r;
    if (p->i488 >= p->c484) return 0;
    {
        BroadcastTaskEvent__FP2SWiP2LO(&g_game, 0x19, p);
        r = PloLaunchReward__FP2LOi(p->p494, (p->ae + p->i488)->nC);
        SetPocketMode__FP2LOi(p, -1);
        p->i488++;
        NextPocketPrize__FP2LO(p);
    }
    return r;
}
