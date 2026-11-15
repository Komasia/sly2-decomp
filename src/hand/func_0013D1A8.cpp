// AkeyStand: the stand's save path: the current world's (0x210A88, 0 when none) progress node, key {the two symbols
// D_002A4BB8 / D_002A4BC0, the stand's id} (SafeHouse booty.cpp: the world's key + booty aoidAssembly <id>).
struct AKEY { int c; short *asym; };   // a save path of symbols
struct STAND { char pad[0x180]; unsigned short id; };
extern "C" {
extern char D_003E0EA8[];
extern char D_002A4BB8[];
extern char D_002A4BC0[];
int func_00210A88(void);
short SymFromName(void *, char *) asm("SymFromName__FP6LAYOUTPc");
void *func_002109B8(int);
void func_001D8CC8(void *, struct AKEY *);
void AkeyStand(struct STAND *pstand) asm("AkeyStand__FP2LO");
}
// name: SafeHouse port (AkeyStand)
void AkeyStand(struct STAND *pstand) {
    short asym[3];
    struct AKEY akey;
    int iwrecCur;
    int iwrec;
    iwrecCur = 0;
    iwrec = func_00210A88();
    if (iwrec == -1) iwrec = iwrecCur;
    iwrecCur = iwrec;
    char *pv = D_003E0EA8;
    pv += 8;
    asym[0] = SymFromName(pv, D_002A4BB8);
    short r = SymFromName(pv, D_002A4BC0);
    register int t __asm__("$3") = pstand->id;
    register int c __asm__("$5") = 3;
    akey.c = c;
    __asm__("" : : : "memory");
    asym[1] = r;
    asym[2] = t;
    akey.asym = asym;
    func_001D8CC8(func_002109B8(iwrecCur), &akey);
}
