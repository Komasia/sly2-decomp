// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
#include "ee_kernel.h"
/* StartThread wrapper (libkernel): start a dormant thread with a clean register context. The saved context
   at the top of its stack is zeroed (keeping the 32-bit values of four slots, sign-extended) and `arg` is put
   in the a0 slot before the real StartThread. The context reset is one noreorder asm block so GNU as does
   not fill the EIntr jal delay slot. */
typedef struct {
    int status; void *entry; char *stack; int stackSize;
    void *gpReg; int initPriority; int currentPriority; unsigned attr;
    unsigned option; int waitType; int waitId; int wakeupCount;
} ThreadParam;
#define THREAD_CONTEXT_SIZE 0x2A0
int func_00235100(void);    /* nonzero inside an interrupt handler (Status.IE clear) */
int DIntr(void);
int EIntr(void);
int ReferThreadStatus(int tid, ThreadParam *info);
int StartThread(int tid, void *arg);

int StartThread_2355E0(int tid, void *arg)
{
    ThreadParam info;
    int ret;
    char *context;

    if (func_00235100() != 0)
        return -1;
    if (DIntr() == 0)
        return -1;
    ret = ReferThreadStatus(tid, &info);
    if (ret < 0) {
        EIntr();
        return ret;
    }
    if (info.status == THS_DORMANT) {
        context = info.stack + info.stackSize - THREAD_CONTEXT_SIZE;
        __asm__ __volatile__(
            ".set noreorder\n\tsq $0, 0x0(%0)\n\tsq $0, 0x10(%0)\n\tsq $0, 0x20(%0)\n\tsq $0, 0x30(%0)\n\t"
            "sq $0, 0x40(%0)\n\tsq $0, 0x50(%0)\n\tsq $0, 0x60(%0)\n\tsq $0, 0x70(%0)\n\t"
            "sq $0, 0x80(%0)\n\tsq $0, 0x90(%0)\n\tsq $0, 0xA0(%0)\n\tsq $0, 0xB0(%0)\n\t"
            "sq $0, 0xC0(%0)\n\tsq $0, 0xD0(%0)\n\tsq $0, 0xE0(%0)\n\tsq $0, 0xF0(%0)\n\t"
            "sq $0, 0x100(%0)\n\tsq $0, 0x110(%0)\n\tsq $0, 0x120(%0)\n\tsq $0, 0x130(%0)\n\t"
            "sq $0, 0x140(%0)\n\tsq $0, 0x150(%0)\n\tsq $0, 0x160(%0)\n\tsq $0, 0x170(%0)\n\t"
            "sq $0, 0x180(%0)\n\tsq $0, 0x190(%0)\n\tsq $0, 0x1A0(%0)\n\tsq $0, 0x1B0(%0)\n\t"
            "sq $0, 0x200(%0)\n\tsq $0, 0x210(%0)\n\tsq $0, 0x220(%0)\n\tsq $0, 0x230(%0)\n\t"
            "sq $0, 0x240(%0)\n\tsq $0, 0x250(%0)\n\tsq $0, 0x260(%0)\n\tsq $0, 0x270(%0)\n\t"
            "sll $8, %1, 0\n\tsd $8, 0x40(%0)\n\t"
            "lw $8, 0x1C0(%0)\n\tsd $8, 0x1C0(%0)\n\tsd $0, 0x1C8(%0)\n\t"
            "lw $8, 0x1D0(%0)\n\tsd $8, 0x1D0(%0)\n\tsd $0, 0x1D8(%0)\n\t"
            "lw $8, 0x1E0(%0)\n\tsd $8, 0x1E0(%0)\n\tsd $0, 0x1E8(%0)\n\t"
            "lw $8, 0x1F0(%0)\n\tsd $8, 0x1F0(%0)\n\tsd $0, 0x1F8(%0)\n\t.set reorder"
            : : "r"(context), "r"(arg) : "$8", "memory");
        EIntr();
        return StartThread(tid, arg);
    }
    EIntr();
    return -1;
}
