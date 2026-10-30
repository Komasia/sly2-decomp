/* func_001AE110 (0x1AE110): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001ADF98(__initialize_p = 1, __priority = 0xFFFF). */
void func_001ADF98(int fInitialize, int nPriority);

void func_001AE110(void)
{
    func_001ADF98(1, 0xFFFF);
}
