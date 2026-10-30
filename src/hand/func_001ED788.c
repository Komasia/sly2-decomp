/* func_001ED788 (0x1ED788): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001ED650(__initialize_p = 1, __priority = 0xFFFF). */
void func_001ED650(int fInitialize, int nPriority);

void func_001ED788(void)
{
    func_001ED650(1, 0xFFFF);
}
