/* func_001F20E8 (0x1F20E8): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001F1FB0(__initialize_p = 1, __priority = 0xFFFF). */
void func_001F1FB0(int fInitialize, int nPriority);

void func_001F20E8(void)
{
    func_001F1FB0(1, 0xFFFF);
}
