/* func_001DE280 (0x1DE280): g++ global-destructor entry of its translation unit: runs the unit's static destruction,
 * func_001DE008(__initialize_p = 0, __priority = 0xFFFF). */
void func_001DE008(int fInitialize, int nPriority);

void func_001DE280(void)
{
    func_001DE008(0, 0xFFFF);
}
