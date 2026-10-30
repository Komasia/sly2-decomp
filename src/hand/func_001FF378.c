/* func_001FF378 (0x1FF378): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001FF188(__initialize_p = 1, __priority = 0xFFFF). */
void func_001FF188(int fInitialize, int nPriority);

void func_001FF378(void)
{
    func_001FF188(1, 0xFFFF);
}
