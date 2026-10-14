typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct E { char pad[0x1C]; float radius; };
struct A { char pad[0x10]; qword v10; char pad2[0x30 - 0x20]; struct E *pe30; };
struct B { char pad[0x10]; int state; char pad2[0x38 - 0x14]; struct E *pe38; };
struct Entry { int kind; int unused; void *object; };
union FLOATWORD { float value; int bits; };
struct Param { int pad[2]; union FLOATWORD *value; };
struct S { char pad[0x190]; qword v190; char pad2[0x1E0 - 0x1A0]; qword v1E0; char pad3[0xFC4 - 0x1F0]; struct Param *param; };
extern qword D_002A2DD0;
qword func_00204E38(struct S *, struct E *, float);
qword func_00204ED8(struct S *, struct E *, float);
void func_0020C0E8(struct B *);
void func_00209618(struct Entry *entry, struct S *s)
{
    U factor, value;
    register qword scalar __asm__("vf1");
    qword extra;
    qword neg;
    value.q = D_002A2DD0;
    extra = value.q;
    switch (entry->kind) {
    case 0:
    case 1:
        {
            struct E *e;
            if (entry->kind == 0) e = (struct E *)entry->object;
            else e = ((struct A *)entry->object)->pe30;
            if (e) {
                value.q = func_00204E38(s, e, e->radius);
                extra = func_00204ED8(s, e, e->radius);
            }
        }
        break;
    case 2:
        {
            struct B *b;
            func_0020C0E8((struct B *)entry->object);
            b = (struct B *)entry->object;
            if (b->state > 0 && (b->state < 3 || b->state == 4)) break;
            value.q = func_00204E38(s, b->pe38, b->pe38->radius);
        }
        break;
    case 3:
        value.q = ((struct A *)entry->object)->v10;
        break;
    }
    if (s->param) {
        __asm__("qmtc2.ni %1, %0" : "=j"(scalar) : "r"(s->param->value->bits));
        factor.q=scalar;
        __asm__("vmulx.xyzw %0, %0, %1x" : "+j"(value.q) : "j"(factor.q));
    }
    s->v1E0 = extra;
    __asm__("qmtc2.ni %1, %0" : "=j"(scalar) : "r"(-1.0f));
    factor.q=scalar;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=&j"(neg) : "j"(value.q), "j"(factor.q));
    s->v190 = neg;
}
