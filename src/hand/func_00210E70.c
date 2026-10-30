/* func_00210E70 (0x210E70): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00210CF0(__initialize_p = 1, __priority = 0xFFFF). */
void func_00210CF0(int fInitialize, int nPriority);

void func_00210E70(void)
{
    func_00210CF0(1, 0xFFFF);
}
