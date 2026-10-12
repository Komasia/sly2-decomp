struct O { char pad[0x26C]; int a; };
struct P { char pad[0x24]; struct O *po; int *pnMin; int *pnMax; int *pn; };
int func_00132B10(struct O *po, int cid);
void func_001EECD0(void *p);
void func_001E5570(struct P *p)
{
    if (p->pnMin < p->pn && p->pn < p->pnMax) {
        switch (*p->pn) {
        case 0x27:
            if (p->po && func_00132B10(p->po, 0x34)) func_001EECD0(&p->po->a);
            break;
        case 0x28:
            if (p->po && func_00132B10(p->po, 0x34)) func_001EECD0(&p->po->a);
            break;
        }
    }
}
