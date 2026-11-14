enum ZPK { ZPK_Nil = -1 };
struct LO;
struct ZPR { ZPK zpk; ZPK zpk2; LO *ploSource; char pad[0x630 - 12]; };
extern "C" void s1_memset(void *p, int c, int n) asm("memset");
void InitZpr(ZPR *pzpr, ZPK zpk, LO *ploSource) { s1_memset(pzpr, 0, sizeof(ZPR)); pzpr->zpk = pzpr->zpk2 = zpk; pzpr->ploSource = ploSource; }
