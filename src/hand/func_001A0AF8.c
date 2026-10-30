/* func_001A0AF8 (0x1A0AF8): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001A09C0(__initialize_p = 1, __priority = 0xFFFF). */
void func_001A09C0(int fInitialize, int nPriority);

void func_001A0AF8(void)
{
    func_001A09C0(1, 0xFFFF);
}
