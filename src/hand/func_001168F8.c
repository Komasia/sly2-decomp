/* func_001168F8 (0x1168F8): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00114AE0(__initialize_p = 1, __priority = 0xFFFF). */
void func_00114AE0(int fInitialize, int nPriority);

void func_001168F8(void)
{
    func_00114AE0(1, 0xFFFF);
}
