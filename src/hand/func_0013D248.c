/* IdStandSaved: the booty a stand holds by the save: 0 its default (+0x184), 7..9 (a player's oid: carried) none (-1),
 * 0x2BF..0x2C1 the same booty as 0x2BC..0x2BE. SafeHouse port (booty.cpp, orig 0x13D248). */
struct STACKSCOPE { int a[4]; };
struct CRef { int m_tagk; int m_n; };
struct STAND { char pad[0x184]; int idDefault; };   /* field: SafeHouse port (0x2BC by default) */
extern char D_003D4A60[];
void __10STACKSCOPE(struct STACKSCOPE *);
void _$_10STACKSCOPE(struct STACKSCOPE *, int);
void *AkeyStand__FP2LO(struct STAND *);
void NProgress(struct CRef *, void *, void *);
void Decref(struct CRef *) asm("Decref__4CRef");
static inline int NFromRef(void *pv)
{
    struct CRef ref;
    int n;
    NProgress(&ref, pv, D_003D4A60);
    n = ref.m_n;
    Decref(&ref);
    return n;
}
// name: SafeHouse port (IdStandSaved)
int IdStandSaved__FP2LO(struct STAND *pstand) {
    struct STACKSCOPE ss;
    int n;
    __10STACKSCOPE(&ss);
    n = NFromRef(AkeyStand__FP2LO(pstand));
    if (n == 0) n = pstand->idDefault;
    else if (n >= 0) { if (n < 10) { if (n >= 7) n = -1; } }
    switch (n) {
    case 0x2bf: n = 0x2bc; break;
    case 0x2c0: n = 0x2bd; break;
    case 0x2c1: n = 0x2be; break;
    }
    _$_10STACKSCOPE(&ss, 2);
    return n;
}
