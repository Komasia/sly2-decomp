/* func_00185110 (0x185110): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00184FD8(__initialize_p = 1, __priority = 0xFFFF). */
void func_00184FD8(int fInitialize, int nPriority);

void func_00185110(void)
{
    func_00184FD8(1, 0xFFFF);
}
