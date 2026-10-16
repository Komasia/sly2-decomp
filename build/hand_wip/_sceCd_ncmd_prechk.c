// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
typedef struct { char p[0x24]; int server; } RpcCD;
extern RpcCD D_002C7910;
extern int D_002C6768;
extern int D_002C6750;
extern int D_002C675C;
extern int D_002C677C;
extern char D_002AB4D0[];
extern char D_002AB4F8[];
void func_00241A30(void);
int func_00234A70(int);
int func_00234A40(int);
int func_00236960(const char *, ...);
int func_00241E88(int);
void func_00236A60(void);
int func_002370A8(void *, unsigned int, int);
int _sceCd_ncmd_prechk(int cmd)
{
    int i;
    func_00241A30();
    if (func_00234A70(D_002C6768) != D_002C6768) {
        if (D_002C6750 > 0) func_00236960(D_002AB4D0, cmd, D_002C675C);
        return 0;
    }
    D_002C675C = cmd;
    if (func_00241E88(1)) {
        func_00234A40(D_002C6768);
        return 0;
    }
    func_00236A60();
    if (D_002C677C < 0) {
        goto bind;
        do {
            i = 0x100000;
            do __asm__ volatile(""); while (i-- != 0);
        bind:
            while (func_002370A8(&D_002C7910, 0x80000595, 0) < 0) {
                if (D_002C6750 > 0) func_00236960(D_002AB4F8);
                i = 0x100000;
                do __asm__ volatile(""); while (i-- != 0);
            }
        } while (D_002C7910.server == 0);
        D_002C677C = 0;
    }
    return 1;
}
