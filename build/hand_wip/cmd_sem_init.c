// (Claude agent) near miss 53/57: logic right; reg alloc of %hi bases (target s1=hi D_002C6768, -1 in v1) differs
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
typedef struct { int count; int max_count; int init_count; int wait_threads; unsigned attr; unsigned option; } ee_sema_t;
extern int D_002C6760, D_002C6768, D_002C676C, D_002C6770, D_002C6774;
extern char D_002AB418[], D_002AB428[], D_002AB438[], D_002AB448[];
int func_00234A20(ee_sema_t *);
void cmd_sem_init(void)
{
    ee_sema_t s;
    if (D_002C6768 == -1 || D_002C676C == -1 || D_002C6770 == -1) {
        s.init_count = 1;
        s.option = (unsigned)D_002AB418;
        s.max_count = 1;
        D_002C6768 = func_00234A20(&s);
        s.option = (unsigned)D_002AB428;
        D_002C676C = func_00234A20(&s);
        s.option = (unsigned)D_002AB438;
        D_002C6770 = func_00234A20(&s);
        s.option = (unsigned)D_002AB448;
        s.init_count = 0;
        D_002C6760 = func_00234A20(&s);
        D_002C6774 = 0;
    }
}
