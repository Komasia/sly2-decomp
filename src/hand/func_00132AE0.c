/* func_00132AE0 (0x132AE0): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001329A8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001329A8(int fInitialize, int nPriority);

void func_00132AE0(void)
{
    func_001329A8(1, 0xFFFF);
}
