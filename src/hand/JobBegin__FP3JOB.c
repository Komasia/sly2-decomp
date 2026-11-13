/* JobBegin: a job begins (its first task reached): the task event 0x1C broadcast, the current player's booty
 * dropped (when it is an actor, cid 0x34), and the job becomes the current one. Source: SafeHouse port (task.cpp). */
struct JOB;
struct LO;
extern char g_game[];
extern char g_sw[];
int FJobCur__FP3JOB(struct JOB *pjob);
void BroadcastTaskEvent__FP2SWiP2LO(void *pgame, int n, struct JOB *pjob);
struct LO *PloPlayerPo__FP2SW(void *psw);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
void DropActorBooty__FP5ACTORii(struct LO *pactor);
void JobSwitch__FP3JOB(struct JOB *pjob);

// name: SafeHouse port (JobBegin)
void JobBegin__FP3JOB(struct JOB *pjob)
{
    if (!FJobCur__FP3JOB(pjob)) {
        struct LO *ploPlayer;
        BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x1C, pjob);
        ploPlayer = PloPlayerPo__FP2SW(g_sw);
        if (ploPlayer != 0 && FIsBasicDerivedFrom__FP5BASIC3CID(ploPlayer, 0x34))
            DropActorBooty__FP5ACTORii(ploPlayer);
        JobSwitch__FP3JOB(pjob);
    }
}
