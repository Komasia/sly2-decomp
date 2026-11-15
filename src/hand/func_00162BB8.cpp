class OBase {
public:
    int a, b, c;
    virtual void V1();
    virtual void V2();
    virtual void Msg(int msgid, int a, int c, void **apv, int d);
};
class O : public OBase {
public:
    char pad[0x50 - 0x10];
    int fDisabled;
    int cnEndClose;     /* events that close the job */
    int *anEndClose;
    int cnEnd;          /* events that end it */
    int *anEnd;
};
struct SW;
extern SW g_sw;
extern "C" int func_00162670(O *p);
extern "C" int func_0020E040(SW *psw);
extern "C" void func_00162DD0(O *p);
extern "C" void func_00162E38(O *p);
extern "C" void RestartJobAtCheckpoint(O *p) asm("RestartJobAtCheckpoint__FP2SW");
/* JobOnEvent: a game event reaches the current job: message 0x11 with the event, then a closing event closes it
 * (func_00162DD0: event 0x1D), an ending event ends it (func_00162E38); a disabled job restarts at its checkpoint on
 * event 0x10. */
// name: SafeHouse port (JobOnEvent)
extern "C" void JobOnEvent__FP3JOBii(O *p, int nEvent, int ploEvent)
{
    if (func_00162670(p)) {
        void *apv[2];
        int i;
        apv[0] = &nEvent;
        apv[1] = &ploEvent;
        p->Msg(0x11, 0, 2, apv, 0);
        for (i = 0; i < p->cnEndClose; i++) {
            if (nEvent == p->anEndClose[i]) {
                func_00162DD0(p);
                break;
            }
        }
        for (i = 0; i < p->cnEnd; i++) {
            if (nEvent == p->anEnd[i]) {
                func_00162E38(p);
                break;
            }
        }
    } else if (nEvent == 0x10 && p->fDisabled && !func_0020E040(&g_sw)) {
        RestartJobAtCheckpoint(p);
    }
}
