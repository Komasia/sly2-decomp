#include "mat.h"
struct CM { char pad[0x90]; struct VECTOR pos; };
void func_0014E168(struct CM *p, struct MATRIX4 *m);
void func_0014F428(struct CM *p, struct MATRIX3 *pmat)
{
    struct MATRIX4 m;
    *(struct MATRIX3 *)&m = *pmat;
    *(struct VECTOR *)m.mat[3] = p->pos;
    m.mat[2][3] = 0.0f;
    m.mat[1][3] = 0.0f;
    m.mat[0][3] = 0.0f;
    func_0014E168(p, &m);
}
