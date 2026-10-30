/* func_00119ED8 (0x119ED8): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00119DA0(__initialize_p = 1, __priority = 0xFFFF). */
void func_00119DA0(int fInitialize, int nPriority);

void func_00119ED8(void)
{
    func_00119DA0(1, 0xFFFF);
}
