// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct { int pad[9]; void *serve; int pad2[6]; } sceSifClientData;
extern int D_002C6750;
extern volatile int D_002C6760;
extern volatile int D_002C6764;
extern volatile int D_002C6768;
extern volatile int D_002C676C;
extern int D_002C6778;
extern int D_002C677C;
extern int D_002C6784;
extern int D_002C6788;
extern int D_002C678C;
extern int D_002C6790;
extern int D_002C6794;
extern int D_002C6798;
extern int D_002C679C;
extern sceSifClientData D_004504E8;
extern int D_00450540[];
extern int D_002C7940[];
int printf(const char *fmt, ...);
int func_00241F28(int);
void func_00236A60(int);
int func_002370A8(sceSifClientData *, unsigned int, int);
void func_0023B170(void *, int);
int func_00237288(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
void func_00241B18(void);
void func_00241A30(void);
void func_00241C10(void);

static __inline__ void nopdelay(void)
{
    int i = 0x100000;
    while (i--) ;
}

int sceCdInit(int mode)
{
    int r, i;
    int *p;
    if (func_00241F28(1)) return 0;
    func_00236A60(0);
    D_002C6764 = 1;
    D_002C6788 = -1;
    D_002C678C = -1;
    D_002C677C = -1;
    D_002C6794 = -1;
    D_002C6790 = -1;
    D_002C6778 = 0;
    D_002C679C++;
    D_002C6798 = -1;
    while (1) {
        int b = func_002370A8(&D_004504E8, 0x80000592, 0);
        if (b < 0) {
            if (D_002C6750 > 0) printf("Libcdvd bind err %d CD_Init %d\n", b, D_002C679C);
            nopdelay();
            continue;
        }
        if (D_004504E8.serve != 0) {
            D_00450540[0] = mode;
            D_002C6798 = 0;
            func_0023B170(D_00450540, 4);
            p = D_002C7940;
            if (func_00237288(&D_004504E8, 0, 0, D_00450540, 4, p, 0x10, 0, 0) < 0) {
                D_002C6764 = 0;
                return 0;
            }
            break;
        }
        nopdelay();
    }
    {
        int b = *(int *)((unsigned int)&p[1] | 0x20000000);
        int c = *(int *)((unsigned int)&p[2] | 0x20000000);
        int a = *(int *)((unsigned int)&p[3] | 0x20000000);
        r = 1;
        if (a == 0xFF) {
        } else if (a == 0xFE) {
            D_002C6750 = 1;
        } else if (b / 256 < 2 || c / 256 < 2) {
            r = 2;
        }
    }
    D_002C6764 = 0;
    switch (mode) {
    case 5:
        if (D_002C6750 > 0) printf("Libcdvd Exit\n");
        func_00241B18();
        D_002C6768 = -1;
        D_002C676C = -1;
        D_002C6760 = -1;
        D_002C6784 = 0;
        break;
    case 0: case 1:
    default:
        func_00241A30();
        func_00241C10();
        D_002C6784 = 1;
        break;
    }
    return r;
}
