typedef int qword __attribute__((mode(TI)));
struct Z { float a; float b; };
struct EN { int a; int b; struct Z *pz; };
struct X { char pad[0x18]; void *p18; float g; };
struct Y { char pad[0x50]; struct X *px; char pad2[0x74 - 0x54]; float f74; char pad3[0xD0 - 0x78]; struct EN *aen; };
struct S { int pad0; struct Y *py; char pad1[0x50 - 8]; float t50; char pad2[0x90 - 0x54]; int h90; float f94; float f98; int af[2]; };
float GModPositive__Fff(float a, float b);
void *PsndNewPlain__Fi(int h);
void SetSource__4CSndPv(void *p, void *source);
qword func_001A62E8(void *p);
void SetPosition__4CSndG9VU_VECTOR(void *p, qword q);
void SetFalloff__4CSndff(void *p, float a, float b);
void SetVolume__4CSndf(void *p, float t);

void func_0020BC08(struct S *p)
{
    struct X *x = p->py->px;
    float g = x->g;
    int i;
    for (i = 0; i < 2; i++) {
        struct Y *y = p->py;
        struct Z *z = y->aen[i].pz;
        int f = z->b <= GModPositive__Fff(g - z->a, y->f74);
        if (f == p->af[i])
            continue;
        if (!f) {
            float t = p->t50;
            void *h;
            { float u = 1.0f - t; t *= p->f98; t += u * p->f94; }
            h = PsndNewPlain__Fi(p->h90);
            SetSource__4CSndPv(h, 0);
            SetPosition__4CSndG9VU_VECTOR(h, func_001A62E8(x->p18));
            SetFalloff__4CSndff(h, 500.0f, 2000.0f);
            SetVolume__4CSndf(h, t);
        }
        p->af[i] = f;
    }
}
