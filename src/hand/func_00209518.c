struct ANIMATION;
struct B {
    char pad[0x24];
    struct ANIMATION *animation24;
    char pad2[8];
    struct ANIMATION *animation30;
    int pad3;
    struct ANIMATION *animation38;
};
struct S { int n; int a; struct B *pb; };

struct ANIMATION *func_00209518(struct S *p)
{
    switch (p->n) {
    case 0: return (struct ANIMATION *)p->pb;
    case 1: return p->pb->animation30;
    case 2: return p->pb->animation38;
    case 3: return p->pb->animation24;
    }
    return 0;
}
