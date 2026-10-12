struct S { char pad[0xE4]; int ne4; };
float func_001E6620(struct S *p);
float func_001E6648(struct S *p);
int func_001C3BB0(struct S *p, float *pg)
{
    /*B*/if (p->ne4) { pg[0] = func_001E6620(p); pg[1] = func_001E6648(p); return 1; } return 0;/*E*/
}
