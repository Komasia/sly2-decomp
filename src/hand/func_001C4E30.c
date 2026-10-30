/* func_001C4E30 (0x1C4E30): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001C4CF8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001C4CF8(int fInitialize, int nPriority);

void func_001C4E30(void)
{
    func_001C4CF8(1, 0xFFFF);
}
