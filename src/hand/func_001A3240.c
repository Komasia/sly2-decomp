/* func_001A3240 (0x1A3240): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001A3108(__initialize_p = 1, __priority = 0xFFFF). */
void func_001A3108(int fInitialize, int nPriority);

void func_001A3240(void)
{
    func_001A3108(1, 0xFFFF);
}
