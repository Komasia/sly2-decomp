typedef int qword __attribute__((mode(TI)));
struct S { char pad[0xE8]; int x; };
struct V { int x, y, z, w; };
qword func_001FAB48(struct S *, qword *, qword);
void func_001FADD0(struct S *p, qword *a, qword b, struct V *pv)
{
    if (!p->x) { pv->z = 0; pv->y = 0; pv->x = 0; }
    else *(qword *)pv = func_001FAB48(p, a, b);
}

#define OFF(T,F) ((unsigned long)&((T*)0)->F)
typedef char velocity_output_layout[(sizeof(qword)==16 && sizeof(void*)==4 && sizeof(int)==4 && sizeof(struct S)==0xEC && OFF(struct S,x)==0xE8 && sizeof(struct V)==16 && OFF(struct V,x)==0 && OFF(struct V,y)==4 && OFF(struct V,z)==8 && OFF(struct V,w)==12)?1:-1];
