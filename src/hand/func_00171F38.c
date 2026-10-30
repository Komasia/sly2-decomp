/* func_00171F38 (0x171F38): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00171E00(__initialize_p = 1, __priority = 0xFFFF). */
void func_00171E00(int fInitialize, int nPriority);

void func_00171F38(void)
{
    func_00171E00(1, 0xFFFF);
}
