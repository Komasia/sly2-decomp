/* func_001A5250 (0x1A5250): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001A5118(__initialize_p = 1, __priority = 0xFFFF). */
void func_001A5118(int fInitialize, int nPriority);

void func_001A5250(void)
{
    func_001A5118(1, 0xFFFF);
}
