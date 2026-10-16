typedef int qword __attribute__((mode(TI)));
typedef struct { short kind,index; union { short item; int value; } payload; } PAIR;
typedef union {qword q;float xyz[4];} VECTOR;
struct CONTACT;
typedef struct { int id,kind; char unknown8[8]; qword value; char unknown20[0x80]; } ENDPOINT;
typedef struct { ENDPOINT endpoint[2]; char unknown140[8]; struct CONTACT *head; int unknown14C; } E;
typedef struct {
    char pad0[0xE4];
    void *xE4;
    char pade8[0x198 - 0xE8];
    int x198;
    E *x19C;
} OBJ;
typedef struct { char pad[0x14]; void **x14; } SUB;
typedef struct { int x0; SUB *x4; } Q;
typedef struct { qword pos; char pad[0x50]; } HIT;
extern char D_003DD490[];
extern PAIR D_002A7AC0;
void func_001F5990(void);
void func_001DEF98(OBJ *,ENDPOINT *,qword *,float *);
int func_0014C6A0(Q *, qword, qword, int, HIT *);
int func_00132B10(void *, int);
int func_00205670(void *, qword, qword, qword *);
void func_001A7C18(void *,void *,Q *,qword,qword,int,int,int,struct CONTACT **,float);
void func_00149AB8(void *,void *,PAIR,int);
static inline int ElementOffset(int index)
{
    register int stride __asm__("$2")=sizeof(E);
    int offset;
    __asm__("mult %0,%1,%2":"=r"(offset):"r"(index),"r"(stride):"hi","lo");
    return offset;
}
static inline int HasEntry(const OBJ *owner,int index)
{
 register int count __asm__("$2")=owner->x198;
 return index<count;
}
void func_001DF0A0(OBJ *p, Q *input)
{
    register Q *q __asm__("$21")=input;
    register int i __asm__("$20");
    func_001F5990();
    for (i = 0; HasEntry(p,i); i++) {
        E *e = (E*)((char*)p->x19C + ElementOffset(i));
        qword out[2];
        VECTOR pos;
        HIT hit;
        register int f __asm__("$17");
        qword *outputs;
        float *distance;
        OBJ *receiver;
        __asm__("daddu %0,%4,$zero\n\t"
                "la %1,%a5\n\t"
                "daddu %2,$zero,$zero\n\t"
                "daddu %3,$zero,$zero"
                : "=r"(receiver),"=r"(outputs),"=r"(distance),"=r"(f)
                : "r"(p),"p"(out));
        func_001DEF98(receiver,e->endpoint,outputs,distance);
        if (!func_0014C6A0(q, out[0], out[1], 1, &hit)) {
            void *so = *q->x4->x14;
            if (func_00132B10(so, 0x33))
                f = func_00205670(so, out[0], out[1], &pos.q);
        } else {
            f = 1;
            pos.q = hit.pos;
        }
        if (f) {
            register qword d __asm__("vf1");
            register qword dir __asm__("vf2");
            register qword len __asm__("vf4");
            register qword start __asm__("vf4")=out[0];
            register qword point __asm__("vf5")=pos.q;
            register int distanceBits __asm__("$2");
            void *ownerState;
            register float zero __asm__("$f12");
            register qword pointArgument __asm__("$7"),directionArgument __asm__("$8");
            register Q *queryArgument __asm__("$6");
            register int distanceArgument __asm__("$10");
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(start), "j"(point));
            dir=out[1];
            // VF1 holds distance, then the normalized direction.
            __asm__("vmul.xyz %0,%0,%0\n\t"
                    "vaddw.x $vf3,$vf0,$vf0w\n\t"
                    "vadday.x $ACC,%0,%0y\n\t"
                    "vmaddz.x %0,$vf3,%0z\n\t"
                    "vsub.xyzw %1,%1,%6\n\t"
                    "vsqrt $Q,%0x\n\t"
                    "vwaitq\n\t"
                    "vaddq.x %0,$vf0,$Q\n\t"
                    "vmul.xyz %2,%1,%1\n\t"
                    "vaddw.x $vf3,$vf0,$vf0w\n\t"
                    "vadday.x $ACC,%2,%2y\n\t"
                    "vmaddz.x %2,$vf3,%2z\n\t"
                    "qmfc2.ni %3,%0\n\t"
                    "vsqrt $Q,%2x\n\t"
                    "vwaitq\n\t"
                    "vaddq.x %2,$vf0,$Q\n\t"
                    "lw %4,%7\n\t"
                    "vdiv $Q,$vf0w,%2x\n\t"
                    "vwaitq\n\t"
                    "vmulq.xyzw %0,%1,$Q\n\t"
                    "mtc1 $zero,%5"
                    : "+j"(d),"+j"(dir),"=j"(len),"=&r"(distanceBits),"=r"(ownerState),"=f"(zero)
                    : "j"(start),"m"(p->xE4)
                    : "vf3");
            __asm__("qmfc2.ni %0,%1":"=r"(pointArgument):"j"(point));
            __asm__("daddu %0,%3,$zero\n\tdaddu %1,%4,$zero\n\tqmfc2.ni %2,%5":"=&r"(queryArgument),"=r"(distanceArgument),"=r"(directionArgument):"r"(q),"r"(distanceBits),"j"(d));
            func_001A7C18(D_003DD490,ownerState,queryArgument,pointArgument,directionArgument,0xA,distanceArgument,0,&e->head,zero);
            func_00149AB8(D_003DD490, p, D_002A7AC0, 0);
        }
    }
}
