/* func_00130888 (0x130888): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00130750(__initialize_p = 1, __priority = 0xFFFF). */
void func_00130750(int fInitialize, int nPriority);

void func_00130888(void)
{
    func_00130750(1, 0xFFFF);
}
