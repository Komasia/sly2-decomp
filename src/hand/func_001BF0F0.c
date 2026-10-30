/* func_001BF0F0 (0x1BF0F0): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001BEFB8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001BEFB8(int fInitialize, int nPriority);

void func_001BF0F0(void)
{
    func_001BEFB8(1, 0xFFFF);
}
