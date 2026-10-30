/* func_001BE378 (0x1BE378): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001BE240(__initialize_p = 1, __priority = 0xFFFF). */
void func_001BE240(int fInitialize, int nPriority);

void func_001BE378(void)
{
    func_001BE240(1, 0xFFFF);
}
