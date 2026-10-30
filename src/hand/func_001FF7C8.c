/* func_001FF7C8 (0x1FF7C8): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001FF690(__initialize_p = 1, __priority = 0xFFFF). */
void func_001FF690(int fInitialize, int nPriority);

void func_001FF7C8(void)
{
    func_001FF690(1, 0xFFFF);
}
