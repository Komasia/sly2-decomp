static inline void Clamp(float *f,float *b) {float lo=b[0],hi=b[1]; if(*f<lo)*f=lo; else if(hi<*f)*f=hi;}
struct VT { char pad[0x40]; short d; short pd; int (*kind)(void *); };
struct M { char pad[0xC]; struct VT *vt; };
struct C { char pad[0x20]; float value; };
struct O { char pad[0xFC4]; struct C *curve; };
struct G { char pad[0x475C]; float offset; };
extern float D_002C3EA0[3];
extern float D_002C3EB0[2];
int func_0015E938(struct G *, int, int, void *);
int func_00132B10(struct O *, int);
struct M *func_001FBB90(int);
void func_001FB2F8(struct M *, struct O *);
void func_001FB4F0(struct M *, float, float);
void func_001FB1F8(struct M *, float);
void func_001FB2C0(struct M *, float);
void func_001FB520(struct M *, float);
void func_00258040(void *, struct M *);
void func_00210740(float offset, float fade, float scale, struct G *p, int id, int oid, int x, int y, struct O *fallback, void *owner, void *unused, void *out)
{
    struct O *o;
    struct M *m;
    if (id == -1)
        return;
    if (oid != -1)
        o = (struct O *)func_0015E938(p, 4, oid, owner);
    else
        o = fallback;
    if (o && func_00132B10(o, 0x38) && o->curve) {
        float v = o->curve->value;
        float f = D_002C3EA0[0] + v * (D_002C3EA0[1] + v * D_002C3EA0[2]);
        Clamp(&f, D_002C3EB0);
        offset += f;
    }
    offset += p->offset;
    m = func_001FBB90(id);
    func_001FB2F8(m, o);
    func_001FB4F0(m, (float)x, (float)y);
    func_001FB1F8(m, scale);
    func_001FB2C0(m, offset);
    func_001FB520(m, fade);
    if (m->vt->kind((char *)m + m->vt->d) == 2)
        func_00258040(out, m);
}
