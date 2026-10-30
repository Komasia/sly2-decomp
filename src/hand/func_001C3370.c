/* func_001C3370 (0x1C3370): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001C3238(__initialize_p = 1, __priority = 0xFFFF). */
void func_001C3238(int fInitialize, int nPriority);

void func_001C3370(void)
{
    func_001C3238(1, 0xFFFF);
}
