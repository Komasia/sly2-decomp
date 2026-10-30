/* func_00148600 (0x148600): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001484C8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001484C8(int fInitialize, int nPriority);

void func_00148600(void)
{
    func_001484C8(1, 0xFFFF);
}
