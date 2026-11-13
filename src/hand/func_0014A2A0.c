struct P { char pad[0x10]; void *x10; int pad1; void *x18; char pad2[0x30 - 0x1C]; int x30; int pad3[2]; int x3C; int x40; int x44; };
extern char g_sw[];
void Update__5AIJOB(struct P *p);
void Aim__8JOBCHASE(struct P *p);
int FJobDone(struct P *p) asm("FJobDone__FP5AIJOB");
int func_00209098(void *p);
int FAirborne__8JOBCHASE(struct P *p);
int IBest__8JOBCHASE(struct P *p);
int PloPlayerPo__FP2SW(void *p);
int PactionSelect__FP5GUARDP2LOP9TARGETREC(void *p, int n, int m);
void SetState__8JOBCHASEi(struct P *p, int k);
void Step__8JOBCHASE(struct P *p);
int FArrived__9JOBFOLLOW(void *p);
int func_00174FB8(void *p);
int func_00175748(void *p);
// name: SafeHouse port (JOBCHASE::Update)
void Update__8JOBCHASE(struct P *p)
{
    int s;
    Update__5AIJOB(p);
    Aim__8JOBCHASE(p);
    for (;;) {
        if (FJobDone(p))
            break;
        s = p->x30;
        switch (s) {
        case 0:
            if (func_00209098(p->x10)) {
                SetState__8JOBCHASEi(p, 4);
            } else if (FAirborne__8JOBCHASE(p)) {
                SetState__8JOBCHASEi(p, 2);
            } else {
                int v = IBest__8JOBCHASE(p);
                p->x40 = v;
                if (v == p->x3C) {
                    int r = PactionSelect__FP5GUARDP2LOP9TARGETREC(p->x10, PloPlayerPo__FP2SW(g_sw), 0);
                    p->x44 = r;
                    if (r)
                        SetState__8JOBCHASEi(p, 3);
                } else {
                    Step__8JOBCHASE(p);
                }
            }
            break;
        case 1:
            if (func_00209098(p->x10))
                SetState__8JOBCHASEi(p, 4);
            else if (FAirborne__8JOBCHASE(p))
                SetState__8JOBCHASEi(p, 2);
            else if (FArrived__9JOBFOLLOW(p->x18))
                SetState__8JOBCHASEi(p, 0);
            else
                PactionSelect__FP5GUARDP2LOP9TARGETREC(p->x10, PloPlayerPo__FP2SW(g_sw), 0);
            break;
        case 2:
            if (func_00209098(p->x10))
                SetState__8JOBCHASEi(p, 4);
            else if (func_00174FB8(p->x18))
                SetState__8JOBCHASEi(p, 0);
            break;
        case 3:
            if (func_00209098(p->x10))
                SetState__8JOBCHASEi(p, 4);
            else if (func_00175748(p->x18))
                SetState__8JOBCHASEi(p, 0);
            break;
        case 4:
            if (!func_00209098(p->x10))
                SetState__8JOBCHASEi(p, 0);
            break;
        }
        if (s == p->x30)
            break;
    }
}
