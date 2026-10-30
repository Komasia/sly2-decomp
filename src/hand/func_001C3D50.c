/* func_001C3D50 (0x1C3D50): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001C3C18(__initialize_p = 1, __priority = 0xFFFF). */
void func_001C3C18(int fInitialize, int nPriority);

void func_001C3D50(void)
{
    func_001C3C18(1, 0xFFFF);
}
