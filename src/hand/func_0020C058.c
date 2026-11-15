/* func_0020C058 (0x20C058): the K2PLAY constructor: its vtable (an ASEGA listener, D_002DAA10), state -1 (none). */
extern int D_002DAA10[];   /* the K2PLAY vtable */
struct K2PLAY { int unk_0x00; int unk_0x04; int unk_0x08; int *pvt; int st; };
struct K2PLAY *func_0020C058(struct K2PLAY *pk2play) { pk2play->pvt = D_002DAA10; pk2play->st = -1; pk2play->unk_0x00 = 0; pk2play->unk_0x04 = 0; return pk2play; }
