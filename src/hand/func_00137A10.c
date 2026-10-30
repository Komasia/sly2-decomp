/* func_00137A10 (0x137A10): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001378D8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001378D8(int fInitialize, int nPriority);

void func_00137A10(void)
{
    func_001378D8(1, 0xFFFF);
}
