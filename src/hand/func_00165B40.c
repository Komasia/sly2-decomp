/* func_00165B40: a next task follows its prerequisite's new state (unless a change is pending on it): locked or
 * available locks it; done / closed with all its prerequisites done unlocks a locked task (a closed one takes the
 * prerequisite's state); otherwise it keeps its state. */
struct TASK { char pad[0x54]; int nState; char pad2[0x94 - 0x58]; int cptaskPrereq; struct TASK **aptaskPrereq; char pad3[0xF0 - 0x9C]; int nPending; };
void func_00165A60(struct TASK *ptask, int nStatePrereq);
void func_00165B40(struct TASK *ptask, int nStatePrereq)
{
    int nStateNew; int nState;
    if (ptask->nPending != -1) return;
    nState = ptask->nState; nStateNew = nState;
    if (nStatePrereq >= 0) {
        if (nStatePrereq < 2) {
            nStateNew = 0;
        } else if (nStatePrereq < 4) {
            int fAllDone = 1;
            int i;
            for (i = 0; i < ptask->cptaskPrereq; i++) {
                if (ptask->aptaskPrereq[i]->nState < 2) {
                    fAllDone = 0;
                    break;
                }
            }
            if (!fAllDone) {
                nStateNew = 0;
            } else {
                switch (ptask->nState) {
                case 0: nStateNew = 1; break;
                case 1: case 2: break;
                case 3: nStateNew = nStatePrereq; break;
                }
            }
        }
    }
    func_00165A60(ptask, nStateNew);
}
