typedef int qword __attribute__((mode(TI)));
typedef struct { float a[6]; } __attribute__((aligned(16))) T;
typedef struct { float a[16]; } __attribute__((aligned(16))) O;
struct RT {char pad[8];void *font;char padC[0x14];qword color0,color1;char pad40[0x20];int changed;float cameraX,cameraY,offsetX,offsetY,width,height,sx,sy,lineHeight,fontScale;int vAlign,hAlign,priority;};
struct DATA {unsigned int color;int mode;float priority;unsigned int limit;qword color0,color1;};

void func_002162D8(struct RT *p, O *po, T *pt);
void func_00216750(struct RT *p, O *po, struct DATA *q);
static inline float Horizontal(const float *p){register float value __asm__("$f2");__asm__("lwc1 %0,%1":"=f"(value):"m"(*p));return value;}
void func_002166B0(struct RT *p, T *pt, struct DATA *q)
{
    T t = *pt;
    O o;
    float x=Horizontal(&t.a[0]),y=t.a[3],g=p->fontScale,shift=p->lineHeight;
    p->sy=y; p->sx=x;
    t.a[0] = x*g;
    t.a[3] = y*g;
    t.a[5] += shift*y;
    func_002162D8(p, &o, &t);
    func_00216750(p, &o, q);
}
