/* func_002310E0 (0x2310E0): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00230FA8(__initialize_p = 1, __priority = 0xFFFF). */
void func_00230FA8(int fInitialize, int nPriority);

void func_002310E0(void)
{
    func_00230FA8(1, 0xFFFF);
}
