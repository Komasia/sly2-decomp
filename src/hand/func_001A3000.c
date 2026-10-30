/* func_001A3000 (0x1A3000): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001A2EC8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001A2EC8(int fInitialize, int nPriority);

void func_001A3000(void)
{
    func_001A2EC8(1, 0xFFFF);
}
