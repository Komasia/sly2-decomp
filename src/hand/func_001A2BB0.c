/* func_001A2BB0 (0x1A2BB0): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001A2A78(__initialize_p = 1, __priority = 0xFFFF). */
void func_001A2A78(int fInitialize, int nPriority);

void func_001A2BB0(void)
{
    func_001A2A78(1, 0xFFFF);
}
