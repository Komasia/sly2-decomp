/* func_00182C50 (0x182C50): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00182B18(__initialize_p = 1, __priority = 0xFFFF). */
void func_00182B18(int fInitialize, int nPriority);

void func_00182C50(void)
{
    func_00182B18(1, 0xFFFF);
}
