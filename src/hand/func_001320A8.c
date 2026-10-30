/* func_001320A8 (0x1320A8): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00131F70(__initialize_p = 1, __priority = 0xFFFF). */
void func_00131F70(int fInitialize, int nPriority);

void func_001320A8(void)
{
    func_00131F70(1, 0xFFFF);
}
