struct CRef {
    int m_tagk;
    int m_tag;
    CRef() { m_tagk = -1; }
    CRef(const CRef &);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &);
    void Decref();
};
struct ENT { int n; int a; };
struct OBJ {
    char pad[0x40];
    int x40;
    int pad44;
    unsigned int c;
    ENT ae[0x40];
    int i;
};
extern char D_002A79A0[];
extern char D_002A79D0[];
extern char D_002A79D8[];
extern "C" int sprintf(char *, const char *, ...) asm("sprintf");
extern "C" CRef func_001D8A38(const char *, ...);
extern "C" int func_001DAE58(int);
extern "C" int func_001DAEA8(int);
extern "C" void SelectShopRow(OBJ *, int) asm("SelectShopRow__FP4SHOPi");
// name: SafeHouse port (BuildShopList)
extern "C" void BuildShopList__FP4SHOP(OBJ *p)
{
    {
        int j;
        for (j = 0; j < (int)p->c; j++)
            p->ae[j].n = -1;
    }
    p->c = 0;
    switch (p->x40) {
    case 0: {
        int i;
        for (i = 7; i < 0x2B; i++) {
            if (!func_001DAE58(i))
                continue;
            if (func_001DAEA8(i))
                continue;
            if (p->c > 0x40)
                break;
            p->ae[p->c++].n = i;
        }
        break;
    }
    case 1: {
        int i;
        for (i = 0; i < 0x40; i++) {
            CRef ref;
            char ach[0x20];
            sprintf(ach, D_002A79A0, i);
            ref = func_001D8A38(D_002A79D0, D_002A79D8, ach, 0);
            if (ref.m_tag == 0)
                continue;
            if (p->c > 0x40)
                break;
            p->ae[p->c++].n = i;
        }
        break;
    }
    }
    SelectShopRow(p, p->i);
}
