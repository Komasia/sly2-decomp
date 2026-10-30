/* func_001C2D00 (0x1C2D00): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001C2BC8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001C2BC8(int fInitialize, int nPriority);

void func_001C2D00(void)
{
    func_001C2BC8(1, 0xFFFF);
}
