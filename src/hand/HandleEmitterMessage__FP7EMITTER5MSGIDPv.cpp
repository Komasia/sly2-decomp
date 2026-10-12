struct EMITTER { char pad[0x14C]; void *p14C; void *p150; };
enum MSGID { MSGID_0, MSGID_1 };
void func_00133448(void *pv, void *po);
void HandleEmitterMessage(EMITTER *pemitter, MSGID msgid, void *pv)
{
    if (msgid == 1) {
        if (pv == pemitter->p14C) {
            func_00133448(pv, pemitter);
            pemitter->p14C = 0;
        } else if (pv == pemitter->p150) {
            func_00133448(pv, pemitter);
            pemitter->p150 = 0;
        }
    }
}
