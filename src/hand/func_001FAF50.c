/* func_001FAF50 (0x1FAF50): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001FAE18(__initialize_p = 1, __priority = 0xFFFF). */
void func_001FAE18(int fInitialize, int nPriority);

void func_001FAF50(void)
{
    func_001FAE18(1, 0xFFFF);
}
