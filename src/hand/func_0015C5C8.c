struct O { char pad[0x100]; void *p100; void *p104; };
void func_00133448(void *pv, void *po);
void HandleExplsMessage__FP5EXPLS5MSGIDPv(struct O *o, int msgid, void *pv)
{
    if (msgid == 1) {
        if (pv == o->p100) {
            func_00133448(pv, o);
            o->p100 = 0;
        } else if (pv == o->p104) {
            func_00133448(pv, o);
            o->p104 = 0;
        }
    }
}
