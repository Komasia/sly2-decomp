/* func_00153D38 (0x153D38): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00153C00(__initialize_p = 1, __priority = 0xFFFF). */
void func_00153C00(int fInitialize, int nPriority);

void func_00153D38(void)
{
    func_00153C00(1, 0xFFFF);
}
