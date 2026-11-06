struct O { char pad[0x60]; int id; };
void Stop__4CSndf(struct O *p, float f);
void func_00258040(struct O **pp, int a);
void func_002108E8(void *a, int id, void *b, struct O **pp)
{
    struct O *p = *pp;
    if (!p)
        return;
    if (id != -1 && p->id != id)
        return;
    Stop__4CSndf(p, 0.0f);
    func_00258040(pp, 0);
}
