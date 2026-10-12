typedef int qword __attribute__((mode(TI)));
typedef union { struct { qword r[4]; } q; float af[4][4]; } M4;
struct CM { char pad[0x60]; M4 mat; };
qword *func_00256D18(qword *p, qword v);
void func_0014E168(struct CM *p, M4 *m);
void func_0014F3C8(struct CM *p, qword pos)
{
    M4 m = p->mat;
    func_00256D18(&m.q.r[3], pos);
    m.af[3][3] = 1.0f;
    func_0014E168(p, &m);
}
