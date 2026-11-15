struct JOBFOLLOW { char pad[0xC0]; int nC0; float gC4; char pad2[0x18]; float gE0; };
extern float D_002BE694;
void func_00177E80(struct JOBFOLLOW *pjob);
/* JOBFOLLOW::Init: the follower base init (func_00177E80), then its follow parameters. */
// name: SafeHouse port (JOBFOLLOW::Init)
void Init__9JOBFOLLOW(struct JOBFOLLOW *pjob) { func_00177E80(pjob); pjob->gE0 = D_002BE694; pjob->gC4 = 1.0f; pjob->nC0 = 9; }
