/* func_001A7BF8 (0x1A7BF8): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001A7AC0(__initialize_p = 1, __priority = 0xFFFF). */
void func_001A7AC0(int fInitialize, int nPriority);

void func_001A7BF8(void)
{
    func_001A7AC0(1, 0xFFFF);
}
