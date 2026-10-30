/* func_001C2900 (0x1C2900): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001C27C8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001C27C8(int fInitialize, int nPriority);

void func_001C2900(void)
{
    func_001C27C8(1, 0xFFFF);
}
