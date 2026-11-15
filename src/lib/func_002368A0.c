// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* Output callback for _sceSnprintf that sends each character to the serial port (kernel printf). */
void serialPutchar(int);
int func_002368A0(void *a, void *b, int c)
{
    if (c) serialPutchar(c);
    return 1;
}
