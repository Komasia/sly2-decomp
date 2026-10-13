struct S {int n;};
enum {TABLE_PAGE=0x003E0000};
void func_001ED560(struct S *input){
    struct S *p;

    register int initial __asm__("$5");
    register int i __asm__("$4");
    register struct S **volatile *firstPage __asm__("$4");
    register struct S **volatile *loopPage __asm__("$8");
    register struct S **firstTable __asm__("$6");
    register struct S **slot __asm__("$2");
    p=input;
    {register int key __asm__("$3")=p->n;initial=key%0x3FFD;}
    firstPage=(struct S **volatile *)TABLE_PAGE;
    __asm__("lw %0,-0x2FE8(%2)\n\tdaddu %1,%2,$zero":"=r"(firstTable),"=r"(loopPage):"r"(firstPage):"memory");
    __asm__("daddu %0,%1,$zero":"=r"(i):"r"(initial));
    slot=(struct S **)((i<<2)+(int)firstTable);
    goto probe;
next:
    {register int nextIndex __asm__("$3")=i+1;i=nextIndex%0x3FFD;}
    {
        register struct S **table __asm__("$5");
        __asm__("lw %0,-0x2FE8(%1)":"=r"(table):"r"(loopPage):"memory");
        slot=(struct S **)((i<<2)+(int)table);
    }
probe:
    if(*slot)goto next;
    *slot=p;
}
