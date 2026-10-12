// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
typedef int qword __attribute__((mode(TI)));
#define REG(a) (*(volatile unsigned int *)(a))
#define FIFO (*(volatile qword *)0x10007010)
extern qword D_002C8550[5];
extern qword D_002C85A0[2];
void setD4_CHCR_00254C28(int);
#define SYNC() while ((int)REG(0x10002010) < 0)
void sceIpuInit(void)
{
    setD4_CHCR_00254C28(1);
    REG(0x10002010) = 0x40000000;
    SYNC();
    REG(0x10002000) = 0;
    SYNC();
    FIFO = D_002C8550[0];
    FIFO = D_002C8550[1];
    FIFO = D_002C8550[2];
    FIFO = D_002C8550[3];
    FIFO = D_002C8550[4];
    FIFO = D_002C8550[4];
    FIFO = D_002C8550[4];
    FIFO = D_002C8550[4];
    REG(0x10002000) = 0x50000000;
    SYNC();
    REG(0x10002000) = 0x58000000;
    SYNC();
    FIFO = D_002C85A0[0];
    FIFO = D_002C85A0[1];
    REG(0x10002000) = 0x60000000;
    SYNC();
    REG(0x10002000) = 0x90000000;
    SYNC();
    REG(0x10002010) = 0x40000000;
    SYNC();
    REG(0x10002000) = 0;
    SYNC();
}
