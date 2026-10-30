/* func_001336D0 (0x1336D0): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00133598(__initialize_p = 1, __priority = 0xFFFF). */
void func_00133598(int fInitialize, int nPriority);

void func_001336D0(void)
{
    func_00133598(1, 0xFFFF);
}
