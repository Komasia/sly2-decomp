/* func_001A02E0 (0x1A02E0): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001A01A8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001A01A8(int fInitialize, int nPriority);

void func_001A02E0(void)
{
    func_001A01A8(1, 0xFFFF);
}
