struct DL { void *head; void *tail; int ibDle; };
struct N { int id; struct N *pnParent; int x8; int xC; int x10; struct N *pnNext; struct DL dl; int pad; };
struct AL { int cb; int cbAlign;  };
extern char D_003DD490[];
void *func_001AE2A0(const struct AL *pal);
void func_0011A050(struct DL *pdl, int ib);
int func_001C9968(int id);
struct DL *func_0015E3C0(void *p, int id);
void func_0011A070(struct DL *pl, void *pv);
struct N *func_001C99D8(struct N *p, int c, const int *input_ids)
{
    register const int*aid __asm__("$18")=input_ids;
    struct N *pn, *pnParent, *pnNew;
    struct AL al;
    int i;
again:
    for (pn = (struct N *)p->dl.head; pn; pn = pn->pnNext) {
        if (pn->id == *aid) {
            if (c == 1) return pn;
            p = pn;
            c--;
            aid++;
            goto again;
        }
    }
    al.cb = c * sizeof(struct N);
    al.cbAlign = 0x10;
    pnNew = (struct N*)func_001AE2A0(&al);
    pnParent = p;
    {register const int*ids __asm__("$19");__asm__ __volatile__("daddu %0,%1,$zero":"=r"(ids):"r"(aid));
    for (i = 0; i < c; i++) {
        pn = &pnNew[i];
        func_0011A050(&pn->dl, 0x14);
        pn->id = *ids++;
        pn->x8 = func_001C9968(pn->id);
        func_0011A070(func_0015E3C0(D_003DD490, pn->x8), pn);
        pn->pnParent = pnParent;
        func_0011A070(&pnParent->dl, pn);
        pnParent = pn;
    }
    }
    return pn;
}

#define OFF(t,m) ((unsigned)&((t*)0)->m)
typedef char tree_layout[(sizeof(void*)==4 && sizeof(int)==4 && sizeof(struct AL)==8 && sizeof(struct N)==0x28 && sizeof(struct DL)==12 && OFF(struct N,id)==0x0 && OFF(struct N,pnParent)==0x4 && OFF(struct N,x8)==0x8 && OFF(struct N,xC)==0xC && OFF(struct N,x10)==0x10 && OFF(struct N,pnNext)==0x14 && OFF(struct N,dl)==0x18 && OFF(struct N,pad)==0x24 && OFF(struct DL,head)==0x0 && OFF(struct DL,tail)==0x4 && OFF(struct DL,ibDle)==0x8 && OFF(struct AL,cb)==0x0 && OFF(struct AL,cbAlign)==0x4)?1:-1];
