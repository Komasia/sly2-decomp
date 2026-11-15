// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31
/* Interface pointer assignment *pp = o: o's vtable slot 1 (add a reference) first, then slot 2 (release) on the
   old object. Each slot is a gcc 2.9 thunk entry {this delta, -, function}. */
typedef struct { int pad[2]; short d1; short p1; void (*f1)(void *); short d2; short p2; void (*f2)(void *); } VT;
typedef struct { int pad[3]; VT *vt; } O;
void func_00258040(O **pp, O *o)
{
    if (o) o->vt->f1((char *)o + o->vt->d1);
    if (*pp) (*pp)->vt->f2((char *)*pp + (*pp)->vt->d2);
    *pp = o;
}
