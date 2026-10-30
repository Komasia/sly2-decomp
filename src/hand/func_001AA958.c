/* func_001AA958 (0x1AA958): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001AA820(__initialize_p = 1, __priority = 0xFFFF). */
void func_001AA820(int fInitialize, int nPriority);

void func_001AA958(void)
{
    func_001AA820(1, 0xFFFF);
}
