struct S { char pad[0x184]; int n; char p1[0x38]; int x1c0; };
extern char g_game[];
int FHackSoHit__FP2LOP5CTMSG(struct S *p, void *message);
void BroadcastTaskEvent__FP2SWiP2LO(void *g, int n, struct S *p);
void SetEnemyState__FP2LOi(struct S *p, int n);
// name: SafeHouse port (FAcceptEnemyContact)
int FAcceptEnemyContact__FP3ALOP5CTMSG(struct S *p, void *message)
{
    register int four __asm__("$2") = 4; if (p->x1c0 == four) return 0;
    if (!FHackSoHit__FP2LOP5CTMSG(p, message)) return 0;
    if (p->n < 0) return 1;
    if (p->n <= 0) BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x18, p);
    SetEnemyState__FP2LOi(p, 4);
    return 1;
}
