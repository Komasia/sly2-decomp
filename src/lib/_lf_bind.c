// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "sif_rpc.h"
/* _lf_bind (libkernel loadfile): bind the IOP LOADFILE RPC server (retrying until it is registered) and read
   its version once. Returns 0, -1 (bind failed) or 0xFFFEFFFF (version call failed). */
#define SIF_RPC_ID_LOADFILE 0x80000006
typedef struct { int pad[9]; void *serve; } SifRpcClientData;
typedef struct { char c[4]; } B4;
extern int D_002C4A98;              /* <0 until bound */
extern SifRpcClientData D_0044C240; /* loadfile client */
extern B4 D_0044C040;               /* receive buffer */
extern B4 D_0044C268;               /* server version */
int sceSifBindRpc(SifRpcClientData *, unsigned int, unsigned int);
int sceSifCallRpc(SifRpcClientData *, int, unsigned int, void *, int, void *, int, void *, void *);
int _lf_bind(void)
{
    int delay;
    if (D_002C4A98 < 0) {
    again:
        if (sceSifBindRpc(&D_0044C240, SIF_RPC_ID_LOADFILE, 0) < 0)
            return -1;
        if (D_0044C240.serve != 0) {
            D_002C4A98 = 0;
            if (sceSifCallRpc(&D_0044C240, 0xFF /* get version */, 0, 0, 0, &D_0044C040, 4, 0, 0) < 0)
                return 0xFFFEFFFF;
            D_0044C268 = D_0044C040;
            return 0;
        }
        delay = 0x100000;     /* server not registered yet: wait and retry */
        do __asm__ volatile(""); while (delay-- != 0);
        goto again;
    }
    return 0;
}
