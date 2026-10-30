/* func_001B2800 (0x1B2800): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001B26C8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001B26C8(int fInitialize, int nPriority);

void func_001B2800(void)
{
    func_001B26C8(1, 0xFFFF);
}
