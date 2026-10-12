struct E { char pad[8]; short h; char pad2[14]; };
struct F { char pad[8]; float f; char pad2[12]; };
struct S { int a; struct F *af; struct E *ae; };
void func_00218060(struct S *p, int i, int j, float f);
void func_00217FE0(struct S *p, int i, int j, float f)
{
    int h;
    float c = 0.0f;
    float one = 1.0f;
    c = (f > c) ? f : c;
    c = (c < one) ? c : one;
    h = p->ae[i].h;
    if (h >= 0)
        func_00218060(p, i, j, p->af[h].f * c);
}
