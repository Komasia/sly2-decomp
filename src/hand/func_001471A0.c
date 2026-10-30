/* func_001471A0 (0x1471A0): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00147068(__initialize_p = 1, __priority = 0xFFFF). */
void func_00147068(int fInitialize, int nPriority);

void func_001471A0(void)
{
    func_00147068(1, 0xFFFF);
}
