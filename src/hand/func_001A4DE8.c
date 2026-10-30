/* func_001A4DE8 (0x1A4DE8): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001A4CB0(__initialize_p = 1, __priority = 0xFFFF). */
void func_001A4CB0(int fInitialize, int nPriority);

void func_001A4DE8(void)
{
    func_001A4CB0(1, 0xFFFF);
}
