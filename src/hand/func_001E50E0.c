struct G { int a; };
extern struct G D_003DD490;
struct P { char pad[0x38]; int fOn; int id; };
void func_0020F030(struct G *pg, int id);
void func_0020F0F0(struct G *pg);
void func_0020EFC0(struct G *pg, int id);
void func_0020F0C0(struct G *pg);
void func_001E50E0(struct P *p, int fOn, int id)
{
if (!fOn) { if (!p->fOn) return; } else { if (p->fOn) { if (id == p->id) return; func_0020F030(&D_003DD490, p->id); func_0020F0F0(&D_003DD490); } func_0020EFC0(&D_003DD490, id); func_0020F0C0(&D_003DD490); p->fOn = fOn; p->id = id; return; } func_0020F030(&D_003DD490, p->id); func_0020F0F0(&D_003DD490); p->fOn = fOn; p->id = id;
}
