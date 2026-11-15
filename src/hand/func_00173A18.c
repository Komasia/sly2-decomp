typedef int qword __attribute__((mode(TI)));
struct SW { int a; };
extern struct SW g_sw;
struct CM { char pad[0x90]; qword pos; };
extern struct CM g_cm;
void *PloPlayerPo__FP2SW(struct SW *psw);
qword PosOfLo__FP2LO(void *plo);
/* PosCenter: the center spawners work around: the player's position, else the camera's (g_cm +0x90). */
// name: SafeHouse port (PosCenter)
qword PosCenter__Fv(void) { struct SW *psw = &g_sw; if (PloPlayerPo__FP2SW(psw)) return PosOfLo__FP2LO(PloPlayerPo__FP2SW(psw)); return g_cm.pos; }
