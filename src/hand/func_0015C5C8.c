struct O { char pad[0x100]; void *p100; void *p104; };
void RemoveLoListener__FP2LOi(void *pv, void *po);
void HandleExplsMessage__FP5EXPLS5MSGIDPv(struct O *o, int msgid, void *pv)
{
    if (msgid == 1) {
        if (pv == o->p100) {
            RemoveLoListener__FP2LOi(pv, o);
            o->p100 = 0;
        } else if (pv == o->p104) {
            RemoveLoListener__FP2LOi(pv, o);
            o->p104 = 0;
        }
    }
}
