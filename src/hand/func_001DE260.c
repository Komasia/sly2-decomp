/* func_001DE260 (0x1DE260): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001DE008(__initialize_p = 1, __priority = 0xFFFF). */
void func_001DE008(int fInitialize, int nPriority);

void func_001DE260(void)
{
    func_001DE008(1, 0xFFFF);
}
