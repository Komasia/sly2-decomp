/* func_001EA548 (0x1EA548): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001EA410(__initialize_p = 1, __priority = 0xFFFF). */
void func_001EA410(int fInitialize, int nPriority);

void func_001EA548(void)
{
    func_001EA410(1, 0xFFFF);
}
