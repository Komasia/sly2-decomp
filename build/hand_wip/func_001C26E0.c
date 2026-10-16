struct LO { char pad[0x28]; unsigned long x28; char p1[0x120 - 0x30]; int x120; int x124; int x128; };
struct G { char pad[0xE94]; int c; int a[(0xFE8 - 0xE98) / 4]; int xFE8; };
static inline struct LO*Receiver(struct LO*p){register struct LO*receiver __asm__("$10");__asm__("daddu %0,%1,$zero":"=r"(receiver):"r"(p));return receiver;}
static inline int Count(const struct G*g){register int value __asm__("$11");__asm__("lw %0,%1":"=r"(value):"m"(g->c));return value;}
int func_001C26E0(void *p, struct LO *plo, struct G *g)
{
    int m, i, f1, f2, c, x1, x2;int*ids;
    plo=Receiver(plo);
    if (!((int)(plo->x28 >> 60) & 1)) return 0;
    m = (plo->x120 == 1) ? 3 : 2;
    if ((m & g->xFE8) != m) return 0;
    {register int one __asm__("$12")=1;c=Count(g);ids=g->a;
    if (c > 0) {
        f1=0;f2=0;i=0;
        if(i<c){
            int value,raw0,raw1;
            {
                register int a __asm__("$2"),b __asm__("$3"),firstFlag __asm__("$8"),secondFlag __asm__("$7"),id0 __asm__("$6"),id1 __asm__("$10");
                __asm__("lw %0,%6\n\tdaddu %3,%9,$zero\n\tlw %1,%7\n\tdaddu %2,%9,$zero\n\tlw $5,%8\n\tdaddu %5,%1,$zero\n\tdaddu %4,%0,$zero\n\txor %1,%1,$5\n\txor %0,%0,$5"
                    :"=&r"(a),"=&r"(b),"=&r"(firstFlag),"=&r"(secondFlag),"=r"(id0),"=r"(id1)
                    :"m"(plo->x124),"m"(plo->x128),"m"(g->a[0]),"r"(one):"$5");
                f1=firstFlag;f2=secondFlag;x1=id0;x2=id1;raw0=a;raw1=b;
            }
            if(raw0)f1=0;if(raw1)f2=0;
            if(f1&&f2)goto found;
            do{
                ++i;if(i>=c)break;
                value=ids[i];
                if(x1==value)f1=1;if(x2==value)f2=1;
                if(f1&&f2)break;
            }while(1);
        }
found:
        if(!f1||!f2)return 0;
    }
    }
    return 1;
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char list_predicate_layout[(sizeof(void*)==0x4 && sizeof(int)==0x4 && sizeof(unsigned long)==0x8 && sizeof(((struct G*)0)->a)==0x150 && OFF(struct LO,x28)==0x28 && OFF(struct LO,x120)==0x120 && OFF(struct LO,x124)==0x124 && OFF(struct LO,x128)==0x128 && OFF(struct G,c)==0xE94 && OFF(struct G,a)==0xE98 && OFF(struct G,xFE8)==0xFE8)?1:-1];
