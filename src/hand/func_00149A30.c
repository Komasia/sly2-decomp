/* func_00149A30 (0x149A30): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001498F8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001498F8(int fInitialize, int nPriority);

void func_00149A30(void)
{
    func_001498F8(1, 0xFFFF);
}
