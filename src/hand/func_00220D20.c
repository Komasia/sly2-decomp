/* func_00220D20 (0x220D20): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00220BE8(__initialize_p = 1, __priority = 0xFFFF). */
void func_00220BE8(int fInitialize, int nPriority);

void func_00220D20(void)
{
    func_00220BE8(1, 0xFFFF);
}
