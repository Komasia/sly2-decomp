class CRef;
extern "C" void func_00129EC8(CRef *pref);
extern "C" CRef*func_001291A8(CRef*,const CRef*);
class CRef {
public:
    int m_tagk;
    int m_tag;
    CRef(bool f) { m_tagk = 0x17; m_tag = f; }
    CRef(const CRef&ref){func_001291A8(this,&ref);}
    ~CRef() { func_00129EC8(this); }
};
class O { public: CRef Fn(const CRef &ref, void *p) asm("func_00258200"); };
struct S { char pad[0x40]; int x40; int x44; float x48; int x4C; };
extern "C" {
extern char D_003DA530[], D_003D9ED0[], D_003D4A60[], D_002E65E0[];
extern O *D_003E0FE4;
int func_001D9880(void *p);
int func_001B0160(void *p);
void func_001ACBB8(S *s);
void func_001ACC38(S *s, int n);
void func_001AF660(void *p);
void func_001DDB08(void *p);
int func_001B0108(void *p);
void func_001AF608(void *p);
void func_001ACB58(S *s, int n);
void func_001ABD40(void *p);
void func_001ACFE0(S *s);
}
static inline void Send(O*object,CRef ref,void*context){object->Fn(ref,context);}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char CRef_m_tagk_Offset[FIELD_OFFSET(CRef,m_tagk)==0?1:-1];
typedef char CRef_m_tag_Offset[FIELD_OFFSET(CRef,m_tag)==4?1:-1];
typedef char S_x40_Offset[FIELD_OFFSET(S,x40)==64?1:-1];
typedef char S_x44_Offset[FIELD_OFFSET(S,x44)==68?1:-1];
typedef char S_x48_Offset[FIELD_OFFSET(S,x48)==72?1:-1];
typedef char S_x4C_Offset[FIELD_OFFSET(S,x4C)==76?1:-1];
typedef char Size_0[sizeof(CRef)==8?1:-1];
typedef char Size_1[sizeof(S)==80?1:-1];
typedef char Size_2[sizeof(int)==4?1:-1];
typedef char Size_3[sizeof(float)==4?1:-1];
typedef char Size_4[sizeof(void*)==4?1:-1];
typedef char Size_5[sizeof(bool)==4?1:-1];
void func_001ACFE0(S *s)
{
    switch (s->x40) {
    case 17: case 18: case 21: case 24:
        {
            void *g = D_003DA530;
            if (func_001D9880(g) && func_001B0160(D_003D9ED0)) {
                func_001ACBB8(s);
                func_001ACC38(s, 2);
                func_001AF660(D_003D9ED0);
                func_001DDB08(g);
                break;
            }
        }
        /* fallthrough */
    case 20: case 23: case 29: case 35: case 36: case 46:
        func_001ACBB8(s);
        func_001ACC38(s, 2);
        if (func_001B0108(D_003D9ED0))
            func_001AF608(D_003D9ED0);
        break;
    case 27: case 28: case 32:
        func_001ACBB8(s);
        break;
    case 34:
        {
            O*object=D_003E0FE4;
            CRef ref(true);
            Send(object,ref,D_003D4A60);
        }
        if (s->x4C < 4) {
            if (s->x4C > 0) {
                func_001ACB58(s, 0x1A);
                func_001ABD40(D_002E65E0);
            }
        }
        break;
    }
}
