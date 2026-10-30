/* func_00205E50 (0x205E50): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00205D18(__initialize_p = 1, __priority = 0xFFFF). */
void func_00205D18(int fInitialize, int nPriority);

void func_00205E50(void)
{
    func_00205D18(1, 0xFFFF);
}
