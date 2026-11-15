struct JOBFOLLOW { char pad[0x4C]; int st; char pad2[0x90]; float gE0; };
/* JOBFOLLOW::FStuck: whether the follow is stuck: in states 0 / 1 with a negative +0xE0. */
// name: SafeHouse port (JOBFOLLOW::FStuck)
int FStuck__9JOBFOLLOW(struct JOBFOLLOW *pjob) { int fStuck = 0; if (pjob->st < 2) { if (pjob->st >= 0) fStuck = pjob->gE0 < 0.0f; } return fStuck; }
