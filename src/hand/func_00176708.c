struct AIMSG { int a[0x1C]; };
void Enter__5AIJOB(void *pjob);
void s1_memset(void *pv, int b, int cb) asm("memset");
void React__8JOBREACTP5AIMSG(void *pjob, struct AIMSG *paimsg);
/* JOBREACT::Enter: the base enter, then reaction message 0 (nothing). */
// name: SafeHouse port (JOBREACT::Enter)
void Enter__8JOBREACT(void *pjob) { struct AIMSG aimsg; Enter__5AIJOB(pjob); s1_memset(&aimsg, 0, sizeof(aimsg)); aimsg.a[0] = 0; React__8JOBREACTP5AIMSG(pjob, &aimsg); }
