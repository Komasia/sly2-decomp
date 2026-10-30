/* func_00160780 (0x160780): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00160648(__initialize_p = 1, __priority = 0xFFFF). */
void func_00160648(int fInitialize, int nPriority);

void func_00160780(void)
{
    func_00160648(1, 0xFFFF);
}
