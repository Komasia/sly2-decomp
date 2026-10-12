// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
typedef struct { void *func; void *data; void *gp; } SifCmdHandlerData;
typedef struct {
    int x0, x4, x8;
    SifCmdHandlerData *sys_cmd_buffer;
    int sys_size;
    SifCmdHandlerData *usr_cmd_buffer;
    int usr_size;
} SifCmdData;
extern SifCmdData D_0044EDD8;

void sceSifAddCmdHandler(int cid, void *handler, void *data)
{
    SifCmdHandlerData *p;
    void *gp;
    if (cid < 0)
    {
        unsigned int i = cid & 0x7FFFFFFF;
        p = &D_0044EDD8.sys_cmd_buffer[i];
        p->func = handler;
        p->data = data;
        __asm__ volatile("move %0, $gp" : "=r"(gp));
        D_0044EDD8.sys_cmd_buffer[i].gp = gp;
    }
    else
    {
        p = &D_0044EDD8.usr_cmd_buffer[cid];
        p->func = handler;
        p->data = data;
        __asm__ volatile("move %0, $gp" : "=r"(gp));
        D_0044EDD8.usr_cmd_buffer[cid].gp = gp;
    }
}
