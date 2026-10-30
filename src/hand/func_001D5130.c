/* func_001D5130 (0x1D5130): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001D4FF8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001D4FF8(int fInitialize, int nPriority);

void func_001D5130(void)
{
    func_001D4FF8(1, 0xFFFF);
}
