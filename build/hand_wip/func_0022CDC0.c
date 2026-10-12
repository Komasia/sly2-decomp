// WIP: 123 diffs but all from ONE missing instruction: target computes q (first k9A switch) into $v0 in every case and copies it
// to $s0 at the join (lh v1,0x9A; por s0,v0); ours assigns $s0 directly in each case. Everything else lines up.
typedef int qword __attribute__((mode(TI)));
typedef union { qword r[4]; float m[4][4]; } M4;
struct O {
    char pad[0x80];
    float g80; float g84; float *pg88; float *pg8C; int x90; int k94; short k98; short k9A; char pad2[0xA8 - 0x9C]; struct O *poA8;
    char pad3[0xB0 - 0xAC]; qword qB0; qword qC0; qword qD0; qword qE0; qword qF0;
};
extern qword D_002A2DD0;
void *func_0023320C(void *d, void *s, int n);
void *func_002333B4(void *p, int c, int n);
M4 *func_0022CCD0(M4 *pm, struct O *pa, struct O *pb, qword v);
M4 *func_0022CB90(M4 *pr, struct O *pa, struct O *pb, qword c, qword d);
M4 *func_0022CC00(M4 *pm, struct O *po, qword v);
qword func_0022CA18(struct O *pa, struct O *pb);
qword func_0011BFF0(qword *pq);
void func_00117120(float g0, float g1, float g2, qword q0, qword q1, qword q2, qword q3, qword *pa, qword *pb, qword *pc);
static __inline__ void Eval(struct O *po, qword *pa, qword *pb, qword *pc)
{
    func_00117120(po->g84 - po->g80, *po->pg88 - po->g80, *po->pg8C, po->qC0, po->qD0, po->qE0, po->qF0, pa, pb, pc);
}
M4 *func_0022CDC0(M4 *pr, struct O *po)
{
    M4 m, m2;
    switch (po->k98) {
    case 0: case 3: case 10: case 12: case 13: case 14: case 15: case 16: case 19:
        func_002333B4(pr, 0, 0x40);
        break;
    default:
        switch (po->k94) {
        case 0: case 2: case 3: case 13: case 15:
            break;
        case 8: case 14: {
            func_0022CDC0(&m, po->poA8);
            func_0023320C(pr, &m, 0x40);
            pr->m[3][0] = -pr->m[3][0];
            pr->m[3][1] = -pr->m[3][1];
            pr->m[3][2] = -pr->m[3][2];
            break;
        }
        case 6: case 7:
            switch (po->k98) {
            case 1: case 2: case 7: case 8: case 9: case 11: case 17: case 18: case 20: case 21: {
                func_0022CCD0(&m, po, po, po->qB0);
                func_0023320C(pr, &m, 0x40);
                break;
            }
            case 5: case 6:
                if (po->k9A == 5) {
                    func_002333B4(pr, 0, 0x40);
                } else {
                    qword q, t;
                    switch (po->k9A) {
                    case 0:
                        q = func_0022CA18(po, po);
                        break;
                    case 1:
                        Eval(po, &m.r[0], 0, 0);
                        q = m.r[0];
                        break;
                    case 2: case 3: case 4:
                        q = po->qC0;
                        break;
                    case 5:
                        q = func_0011BFF0(&po->qC0);
                        break;
                    default:
                        q = D_002A2DD0;
                        break;
                    }
                    switch (po->k9A) {
                    case 3: case 4:
                        t = po->qD0;
                        break;
                    case 1:
                        Eval(po, 0, &m.r[0], 0);
                        t = m.r[0];
                        break;
                    case 0: case 2: case 5: default:
                        t = D_002A2DD0;
                        break;
                    }
                    func_0022CB90(&m, po, po, q, t);
                    func_0023320C(pr, &m, 0x40);
                }
                break;
            }
            break;
        default: {
            switch (po->k98) {
            case 1: case 2: case 7: case 8: case 9: case 11: case 17: case 18: case 20: case 21:
                m.r[0] = po->qB0;
                break;
            case 5: case 6:
                switch (po->k9A) {
                case 1:
                    Eval(po, 0, &m.r[1], 0);
                    m.r[0] = m.r[1];
                    break;
                case 3: case 4:
                    m.r[0] = po->qD0;
                    break;
                default:
                    m.r[0] = D_002A2DD0;
                    break;
                }
                break;
            }
            func_0022CC00(&m2, po, m.r[0]);
            func_0023320C(pr, &m2, 0x40);
            break;
        }
        }
        break;
    }
    return pr;
}
