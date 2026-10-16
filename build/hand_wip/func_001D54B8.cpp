extern "C" {
typedef struct { int m_tagk; int m_tag; } CRef;
typedef struct G G;
extern G D_003D4A60;
extern void *D_003E0FD8;
extern int D_002C2D8C;
CRef *func_001291A8(CRef *,const CRef *);
void func_00129EC8(CRef *);
CRef *func_00258200(CRef *,void *,const CRef *,G *);
static inline void SetRef(void *pv, CRef *pref)
{
    CRef tmp;
    CRef ret;
    func_001291A8(&tmp, pref);
    func_00258200(&ret, pv, &tmp, &D_003D4A60);
    func_00129EC8(&ret);
    func_00129EC8(&tmp);
}
void func_001D54B8(void)
{
    CRef ref;
    switch (D_002C2D8C) {
    case 1:break;
    case 2:
        ref.m_tagk = 0x17;
        ref.m_tag = 0;
        {register void *property __asm__("$17")=D_003E0FD8;SetRef(property,&ref);}
        func_00129EC8(&ref);
        break;
    case 3:
        ref.m_tag = 1;
        ref.m_tagk = 0x17;
        {register void *property __asm__("$16")=D_003E0FD8;SetRef(property,&ref);}
        func_00129EC8(&ref);
        break;
    }
}

}
