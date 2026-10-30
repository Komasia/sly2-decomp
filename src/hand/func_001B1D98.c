/* func_001B1D98 (0x1B1D98): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001B1C60(__initialize_p = 1, __priority = 0xFFFF). */
void func_001B1C60(int fInitialize, int nPriority);

void func_001B1D98(void)
{
    func_001B1C60(1, 0xFFFF);
}
