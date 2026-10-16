/* (Claude agent) structure now matches target exactly (count reload in loop via goto loop, no LICM); only register renaming differs: target i=a1,reload=a2,key=a3,a=t0 */
struct MSG{int kind;};
struct OWNER;
struct S{struct MSG msg;int word4;int x8;int*xC;int pad[3];unsigned flags;};
extern struct OWNER D_003D9ED0;
void func_001AFB88(struct OWNER *g,struct MSG *s);
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
void func_001AFFC0(struct S *s)
{
    int i = 0; int count = s->x8; int *a = s->xC;
    if (count > 0) {
        int first = a[0]; int key = s->msg.kind;
        if (key == first) { i = 1; s->msg.kind = a[i % count]; }
        else {
        loop:
            i++;
            if (i >= s->x8) goto done;
            if (key != a[i]) goto loop;
            i++; s->msg.kind = a[i % s->x8];
        }
    }
done:
    func_001AFB88(&D_003D9ED0, &s->msg);
    s->flags |= 2;
}
