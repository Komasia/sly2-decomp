/* func_001F1748 (0x1F1748): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001F1610(__initialize_p = 1, __priority = 0xFFFF). */
void func_001F1610(int fInitialize, int nPriority);

void func_001F1748(void)
{
    func_001F1610(1, 0xFFFF);
}
