/* HandleBombMessage: message 4 about the projectile itself ends a kind-0 projectile's flight now. */
struct BOMB { char pad[0x150]; int kind; };
struct MSGT { int f0; struct BOMB *pbomb; };
void func_00133590(struct BOMB *, int, struct MSGT *);   /* the base handler (empty) */
void ExpireIn__FP3ALOf(struct BOMB *, float);
void HandleBombMessage__FP4BOMB5MSGIDPv(struct BOMB *pbomb, int msg, struct MSGT *pm) {
    func_00133590(pbomb, msg, pm);
    if (msg == 4 && pm->pbomb == pbomb && pbomb->kind == 0) ExpireIn__FP3ALOf(pbomb, 0.0f);
}
