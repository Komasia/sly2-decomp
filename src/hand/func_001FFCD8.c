/* func_001FFCD8 (0x1FFCD8): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001FFBA0(__initialize_p = 1, __priority = 0xFFFF). */
void func_001FFBA0(int fInitialize, int nPriority);

void func_001FFCD8(void)
{
    func_001FFBA0(1, 0xFFFF);
}
