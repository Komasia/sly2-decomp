/* func_00114AC0 (0x114AC0): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001147D8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001147D8(int fInitialize, int nPriority);

void func_00114AC0(void)
{
    func_001147D8(1, 0xFFFF);
}
