/* 16/45 differ: count reloads and search-register allocation. */
struct S { int x0; int x4; int x8; int *xC; int pad[3]; int x1C; };
extern char D_003D9ED0[];
void func_001AFB88(void *g, struct S *s);
void func_001AFFC0(struct S *s)
{
    int i=0;int count=s->x8;int *a=s->xC;if(count>0){int first=a[0];int key=s->x0;if(key==first){i=1;s->x0=a[i%count];}else{while(++i<s->x8){if(key==a[i]){i++;s->x0=a[i%s->x8];break;}}}}
    func_001AFB88(D_003D9ED0, s);
    s->x1C |= 2;
}
