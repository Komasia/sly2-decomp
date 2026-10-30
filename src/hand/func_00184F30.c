/* func_00184F30 (0x184F30): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00184DF8(__initialize_p = 1, __priority = 0xFFFF). */
void func_00184DF8(int fInitialize, int nPriority);

void func_00184F30(void)
{
    func_00184DF8(1, 0xFFFF);
}
