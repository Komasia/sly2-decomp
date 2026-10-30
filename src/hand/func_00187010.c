/* func_00187010 (0x187010): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00186ED8(__initialize_p = 1, __priority = 0xFFFF). */
void func_00186ED8(int fInitialize, int nPriority);

void func_00187010(void)
{
    func_00186ED8(1, 0xFFFF);
}
