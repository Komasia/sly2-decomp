struct LO { char pad[0x28]; unsigned long x28; char p1[0x120 - 0x30]; int x120; int x124; int x128; };
struct G { char pad[0xE94]; int c; int a[(0xFE8 - 0xE98) / 4]; int xFE8; };
static inline int Entry(const struct G*g,int i){int*address;int value;__asm__("sll %0,%2,2\n\taddu %0,%0,%1":"=&r"(address):"r"(g->a),"r"(i));__asm__("lw %0,%1":"=r"(value):"m"(*address));return value;}
static inline struct LO*Receiver(struct LO*p){register struct LO*receiver __asm__("$10");__asm__("daddu %0,%1,$zero":"=r"(receiver):"r"(p));return receiver;}
static inline int ID0(const struct LO*p){register int value __asm__("$2");__asm__("lw %0,%1":"=r"(value):"m"(p->x124));return value;}
static inline int ID1(const struct LO*p){register int value __asm__("$3");__asm__("lw %0,%1":"=r"(value):"m"(p->x128));return value;}
static inline int FirstEntry(const struct G*g){register int value __asm__("$5");__asm__("lw %0,%1":"=r"(value):"m"(g->a[0]));return value;}
static inline int FirstFlag(int one){register int value __asm__("$8");__asm__("daddu %0,%1,$zero":"=r"(value):"r"(one));return value;}
static inline int SecondFlag(int one){register int value __asm__("$7");__asm__("daddu %0,%1,$zero":"=r"(value):"r"(one));return value;}
static inline int SavedID0(int id){register int value __asm__("$6");__asm__("daddu %0,%1,$zero":"=r"(value):"r"(id));return value;}
static inline int SavedID1(int id){register int value __asm__("$10");__asm__("daddu %0,%1,$zero":"=r"(value):"r"(id));return value;}
static inline int Count(const struct G*g){register int value __asm__("$11");__asm__("lw %0,%1":"=r"(value):"m"(g->c));return value;}
static inline int*EntryBase(const struct G*g){register int*value __asm__("$13");__asm__("addiu %0,%1,0xE98":"=r"(value):"r"(g));return value;}
int func_001C26E0(void *p, struct LO *plo, struct G *g)
{
    int m, i, f1, f2, c, x1, x2;int*ids;
    plo=Receiver(plo);
    if (!((int)(plo->x28 >> 60) & 1)) return 0;
    m = (plo->x120 == 1) ? 3 : 2;
    if ((m & g->xFE8) != m) return 0;
    c=Count(g);ids=EntryBase(g);
    if (c > 0) {
        f1=0;f2=0;i=0;
        if(i<c){
            int value,raw0,raw1;
            raw0=ID0(plo);f2=SecondFlag(1);raw1=ID1(plo);f1=FirstFlag(1);
            value=FirstEntry(g);x2=SavedID1(raw1);x1=SavedID0(raw0);
            if(raw0!=value)f1=0;if(raw1!=value)f2=0;
            if(f1&&f2)goto found;
            do{
                ++i;if(i>=c)break;
                value=Entry((const struct G*)((char*)ids-0xE98),i);
                if(x1==value)f1=1;if(x2==value)f2=1;
                if(f1&&f2)break;
            }while(1);
        }
found:
        if(!f1||!f2)return 0;
    }
    return 1;
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char list_predicate_layout[(sizeof(void*)==0x4 && sizeof(int)==0x4 && sizeof(unsigned long)==0x8 && sizeof(((struct G*)0)->a)==0x150 && OFF(struct LO,x28)==0x28 && OFF(struct LO,x120)==0x120 && OFF(struct LO,x124)==0x124 && OFF(struct LO,x128)==0x128 && OFF(struct G,c)==0xE94 && OFF(struct G,a)==0xE98 && OFF(struct G,xFE8)==0xFE8)?1:-1];
