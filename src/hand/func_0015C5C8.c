/* HandleExplsMessage: on message 1 (an object going away) drop the explosion's RIP group / particle system (+0x100 / +0x104),
 * unregistering from it first. */
struct EXPLS { char pad[0x100]; void *pripg; void *ppsys; };   /* field: SafeHouse port - its RIP group / particle system */
void func_00133448(void *pv, void *pexpls);
void HandleExplsMessage__FP5EXPLS5MSGIDPv(struct EXPLS *pexpls, int msgid, void *pv)
{
    if (msgid == 1) {
        if (pv == pexpls->pripg) {
            func_00133448(pv, pexpls);
            pexpls->pripg = 0;
        } else if (pv == pexpls->ppsys) {
            func_00133448(pv, pexpls);
            pexpls->ppsys = 0;
        }
    }
}
