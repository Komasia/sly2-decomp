/* func_001553D0 (0x1553D0): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00155298(__initialize_p = 1, __priority = 0xFFFF). */
void func_00155298(int fInitialize, int nPriority);

void func_001553D0(void)
{
    func_00155298(1, 0xFFFF);
}
