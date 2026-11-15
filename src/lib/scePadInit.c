// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "libpad_rpc.h"
/* scePadInit (libpad): bind the two padman RPC servers, check the module version, then scePadInit2. 1 on success. */
typedef struct { char p[0x24]; int server; char q[0x28 - 0x28]; } RpcCD;
extern RpcCD D_00450580[2];     /* padman RPC clients */
extern int D_002C8308;          /* libpad initialised */
extern int D_002C830C;          /* debug prints enabled */
extern char D_002AB680[];       /* "libpad: Module version mismatch " */
extern char D_002AB6A8[];       /* "[libpad.a = %d.%d, padman.irx = %d.%d]\n" */
int sceSifBindRpc(void *, unsigned int, int);
int scePadGetModVersion(void);
int scePrintf(const char *, ...);
int scePadInit2(int);
int scePadInit(int mode)
{
    int i;
    int ver;
    D_002C8308 = 1;
    while (sceSifBindRpc(&D_00450580[0], PAD_RPC_ID_CMD, 0), D_00450580[0].server == 0) {
        i = 0x10000;
        do __asm__ volatile(""); while (i-- != 0);
    }
    while (sceSifBindRpc(&D_00450580[1], PAD_RPC_ID_EXT, 0), D_00450580[1].server == 0) {
        i = 0x10000;
        do __asm__ volatile(""); while (i-- != 0);
    }
    ver = scePadGetModVersion();
    if ((ver >> 8) != 4) {      /* needs padman 4.x */
        if (D_002C830C) {
            scePrintf(D_002AB680);
            scePrintf(D_002AB6A8, 4, 0, ver >> 8, ver & 0xFF);
        }
        return 0;
    }
    return scePadInit2(mode);
}
