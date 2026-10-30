/* func_00131F50 (0x131F50): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00131E18(__initialize_p = 1, __priority = 0xFFFF). */
void func_00131E18(int fInitialize, int nPriority);

void func_00131F50(void)
{
    func_00131E18(1, 0xFFFF);
}
