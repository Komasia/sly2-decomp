/* func_001CC138 (0x1CC138): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001CC000(__initialize_p = 1, __priority = 0xFFFF). */
void func_001CC000(int fInitialize, int nPriority);

void func_001CC138(void)
{
    func_001CC000(1, 0xFFFF);
}
