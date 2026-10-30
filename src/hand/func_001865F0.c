/* func_001865F0 (0x1865F0): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001864B8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001864B8(int fInitialize, int nPriority);

void func_001865F0(void)
{
    func_001864B8(1, 0xFFFF);
}
