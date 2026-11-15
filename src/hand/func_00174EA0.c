struct KINDSUB { char pad[0x10]; int kind; };
struct KINDE { int kind; int b; struct KINDSUB *psub; };
struct JOBMOVE { char pad[0x40]; struct KINDE *pkinde; };
int State__5AIJOB(struct JOBMOVE *pjob);
/* JOBMOVE::State: the job's AI state: an entry of kind 2 reports 7 or 1 by its sub-kind, else the base's. */
// name: SafeHouse port (JOBMOVE::State)
int State__7JOBMOVE(struct JOBMOVE *pjob) {
    if (pjob->pkinde->kind == 2) {
        switch (pjob->pkinde->psub->kind) { case 0: case 3: case 4: return 7; default: return 1; }
    }
    return State__5AIJOB(pjob);
}
