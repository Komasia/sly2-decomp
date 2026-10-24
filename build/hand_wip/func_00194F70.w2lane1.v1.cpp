typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
struct O;struct PROVIDER;struct SMP{float speed,terminal,time;};
typedef struct { short d; short pad; int (*pfn)(void *, float *); } VTA1;
typedef struct { short d; short pad; void (*pfn)(void *, void *, qword *, void *, float); } VTA3;
typedef union { VTA1 v1; VTA3 v3; } VTA;
typedef struct { short d; short pad; void (*pfn)(void *, qword); } VTL;
struct A { char pad[0x14]; int x14; char pad2[0x20 - 0x18]; VTA *vt; };
struct L { char pad[0xC]; VTL *vt; };
typedef struct { O*x0; struct A *x4; float x8; int xc; struct L *x10; float x14; float x18; float x1c; qword position; } __attribute__((aligned(16))) E;
struct P { char pad[0x4678]; int c; E ae[4]; };
struct Q { char pad[0x9C4]; PROVIDER*x9C4; };
struct CLOCK { float t; float dt; };
extern "C" { extern struct CLOCK D_002DDED0;
extern int D_002E1E50;
extern float D_002BF710, D_002BF714;
extern SMP D_002BF718;
extern char D_002DEB30[]; }
extern "C" {
int func_00194F48(const void *, const void *);
void func_002338C0(void *base, uint n, uint cb, int (*cmp)(const void *, const void *));
void *func_002332B8(void *dst, const void *src, uint cb);
float func_0011D018(float,float,float,SMP*,float*);
void func_001F7BF8(void *p, float f);
void func_001619A0(void*p,int message,void*object);
struct L *func_001956D0(struct P *p, PROVIDER*x, E*pe);
void func_00194F70(struct P *p, struct Q *pq, int n, E *ae);
}
struct MERGE_WORK { float bounds[2]; qword point; Q*subject; E*owned; };
static inline E*Entry(E*base,int index){return base+index;}
static inline int ExistingCount(const P*p){return p->c;}
static inline E*OwnedAddress(P*p){return p->ae;}
static inline E*ExistingEntry(P*p,int index){return p->ae+index;}
static inline L*NewLinkResult(L*input){return input;}
void func_00194F70(struct P *p, struct Q *pq, int n, E *ae)
{
    MERGE_WORK work;work.subject=pq;
    int i, j;
    E *e,*a;
    if (n > 0) {
        func_002338C0(ae, n, 0x30, func_00194F48);
        if (ae->x4->x14 != -1) ae->xc = 1;
    }
    work.owned=OwnedAddress(p);
    i = ExistingCount(p);
    for (; --i >= 0; ) {
        e = ExistingEntry(p,i);
        j = n;
        goto test;
        O *x0;
        do {
    top:
        x0 = e->x0;
        a = Entry(ae,j);
        } while (0);
        if (x0 == a->x0) {
            e->x8 = a->x8;
            if (!e->x10) {
                e->x18 = a->x18;
                e->x1c = 0.0f;
            } else {

                float w;
                int fWrap = a->x4->vt[1].v1.pfn((char *)a->x4 + a->x4->vt[1].v1.d, work.bounds);
                if (fWrap) {
                    float d;
                    w = work.bounds[1] - work.bounds[0];
                    float av = a->x18;
                    float ex = e->x18;
                    d = av - ex;
                    if (w * 0.5f < d) {
                        d -= w;
                        goto store;
                    } else if (d < w * -0.5f) {
                        d += w;
                    store:
                        a->x18 = ex + d;
                    } else {
                        fWrap = 0;
                    }
                }
                if (D_002E1E50) {
                    float dt = D_002DDED0.dt;
                    float v = e->x1c;
                    float vNew = v + dt * ((a->x18 - e->x18) * D_002BF710 + (a->x1c - v) * D_002BF714);
                    float vAvg;
                    e->x1c = vNew;
                    vAvg = (v + vNew) * 0.5f;
                    e->x18 = e->x18 + dt * vAvg;
                } else {
                    e->x18 = func_0011D018(e->x18, a->x18, D_002DDED0.dt, &D_002BF718, &e->x1c);
                }
                if (fWrap) {
                    if (work.bounds[1] < e->x18) e->x18 = e->x18 - w;
                    else if (e->x18 < work.bounds[0]) e->x18 = e->x18 + w;
                }
                A*object=e->x4;
                object->vt[3].v3.pfn((char*)object+object->vt[3].v3.d,work.subject,&work.point,0,e->x18);

                e->x10->vt[29].pfn((char *)e->x10 + e->x10->vt[29].d, work.point);
            }
            func_002332B8(a, a + 1, (n - j) * 0x30 - 0x30);
            n--;
            goto next;
        }
    test:
        if (--j >= 0) goto top;
        if (e->x10) func_001F7BF8(e->x10, 0.5f);
        func_002332B8(e, e + 1, (3 - i) * 0x30);
        p->c--;
    next:;
    }
    for (j = 0; j < n; j++) {
        a = &ae[j];
        Q*subject=work.subject;
        if (subject->x9C4 && a->xc == 1) {
            struct L *r = NewLinkResult(func_001956D0(p, subject->x9C4, a));
            if (!r) break;
            a->x10 = r;
        }
        p->ae[p->c++] = *a;
        func_001619A0(D_002DEB30, 0x3D, a->x0);
    }
    func_002338C0(work.owned, p->c, 0x30, func_00194F48);
}

#define OFF(t,m) ((uint)&(((t*)0)->m))
typedef char Pointer_size[sizeof(void*)==4?1:-1];
typedef char Int_size[sizeof(int)==4?1:-1];
typedef char UInt_size[sizeof(uint)==4?1:-1];
typedef char Float_size[sizeof(float)==4?1:-1];
typedef char Short_size[sizeof(short)==2?1:-1];
typedef char Qword_size[sizeof(qword)==16?1:-1];
typedef char Qword_alignment[__alignof__(qword)==16?1:-1];
typedef char VTA1_size[sizeof(VTA1)==8?1:-1];
typedef char VTA3_size[sizeof(VTA3)==8?1:-1];
typedef char VTA_size[sizeof(VTA)==8?1:-1];
typedef char VTL_size[sizeof(VTL)==8?1:-1];
typedef char VTA1_delta[OFF(VTA1,d)==0?1:-1];
typedef char VTA1_function[OFF(VTA1,pfn)==4?1:-1];
typedef char VTA3_delta[OFF(VTA3,d)==0?1:-1];
typedef char VTA3_function[OFF(VTA3,pfn)==4?1:-1];
typedef char VTL_delta[OFF(VTL,d)==0?1:-1];
typedef char VTL_function[OFF(VTL,pfn)==4?1:-1];
typedef char A_prefix[sizeof(A)==0x24?1:-1];
typedef char A_cue[OFF(A,x14)==0x14?1:-1];
typedef char A_vtable[OFF(A,vt)==0x20?1:-1];
typedef char L_prefix[sizeof(L)==0x10?1:-1];
typedef char L_vtable[OFF(L,vt)==0xC?1:-1];
typedef char E_size[sizeof(E)==0x30?1:-1];
typedef char E_alignment[__alignof__(E)==16?1:-1];
typedef char E_object[OFF(E,x0)==0?1:-1];
typedef char E_sample[OFF(E,x4)==4?1:-1];
typedef char E_distance[OFF(E,x8)==8?1:-1];
typedef char E_priority[OFF(E,xc)==0xC?1:-1];
typedef char E_link[OFF(E,x10)==0x10?1:-1];
typedef char E_time[OFF(E,x14)==0x14?1:-1];
typedef char E_parameter[OFF(E,x18)==0x18?1:-1];
typedef char E_speed[OFF(E,x1c)==0x1C?1:-1];
typedef char E_point[OFF(E,position)==0x20?1:-1];
typedef char P_prefix[sizeof(P)==0x4740?1:-1];
typedef char P_count[OFF(P,c)==0x4678?1:-1];
typedef char P_entries[OFF(P,ae)==0x4680?1:-1];
typedef char Q_prefix[sizeof(Q)==0x9C8?1:-1];
typedef char Q_provider[OFF(Q,x9C4)==0x9C4?1:-1];
typedef char SMP_size[sizeof(SMP)==12?1:-1];
typedef char SMP_speed[OFF(SMP,speed)==0?1:-1];
typedef char SMP_terminal[OFF(SMP,terminal)==4?1:-1];
typedef char SMP_time[OFF(SMP,time)==8?1:-1];
typedef char CLOCK_size[sizeof(CLOCK)==8?1:-1];
typedef char CLOCK_time[OFF(CLOCK,t)==0?1:-1];
typedef char CLOCK_delta[OFF(CLOCK,dt)==4?1:-1];
typedef char WORK_size[sizeof(MERGE_WORK)==0x30?1:-1];
typedef char WORK_alignment[__alignof__(MERGE_WORK)==16?1:-1];
typedef char WORK_bounds[OFF(MERGE_WORK,bounds)==0?1:-1];
typedef char WORK_point[OFF(MERGE_WORK,point)==0x10?1:-1];
typedef char WORK_subject[OFF(MERGE_WORK,subject)==0x20?1:-1];
typedef char WORK_owned[OFF(MERGE_WORK,owned)==0x24?1:-1];
