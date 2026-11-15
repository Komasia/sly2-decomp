// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
int DisableIntc(int);
int RemoveIntcHandler(int, int);
extern int _sif_cmd_handler_id; extern int _sif_cmd_inited;
#define INTC_SBUS 5
/* sceSifExitCmd (libkernel sifcmd): stop handling SIF commands (unhook the SBUS interrupt). */
void sceSifExitCmd(void)
{
    DisableIntc(INTC_SBUS);
    RemoveIntcHandler(INTC_SBUS, _sif_cmd_handler_id);
    _sif_cmd_inited = 0;
}
