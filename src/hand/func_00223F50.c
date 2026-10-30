/* func_00223F50 (0x223F50): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00223E18(__initialize_p = 1, __priority = 0xFFFF). */
void func_00223E18(int fInitialize, int nPriority);

void func_00223F50(void)
{
    func_00223E18(1, 0xFFFF);
}
