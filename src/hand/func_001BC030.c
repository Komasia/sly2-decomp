/* func_001BC030 (0x1BC030): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001BBEF8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001BBEF8(int fInitialize, int nPriority);

void func_001BC030(void)
{
    func_001BBEF8(1, 0xFFFF);
}
