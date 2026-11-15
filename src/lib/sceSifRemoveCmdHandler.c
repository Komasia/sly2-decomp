// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
typedef struct { void *func; void *data; int gp; } SifCmdHandler;
extern SifCmdHandler *_sif_sys_handlers; extern SifCmdHandler *_sif_usr_handlers;

/* sceSifRemoveCmdHandler (libkernel sifcmd): unregister the handler of command `cid` (system ids have the top
   bit set). */
void sceSifRemoveCmdHandler(int cid)
{
    if (cid < 0) _sif_sys_handlers[cid & 0x7fffffff].func = 0;
    else _sif_usr_handlers[cid].func = 0;
}
