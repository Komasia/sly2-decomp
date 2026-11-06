struct S { char pad[0x174]; void *p174; };
void func_00133590(struct S *p, int n);
void Stop__4CSndf(void *p, float g);
void func_00258040(void **pp, int n);
void HandlePoMessage__FP2PO5MSGIDPv(struct S *p, int n)
{
    func_00133590(p, n);
    if (n == 5) {
        void **pp = &p->p174;
        if (pp && *pp) {
            Stop__4CSndf(*pp, 0.0f);
            func_00258040(pp, 0);
        }
    }
}
