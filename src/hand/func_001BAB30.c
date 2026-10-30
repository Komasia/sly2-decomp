/* func_001BAB30 (0x1BAB30): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001BA9F8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001BA9F8(int fInitialize, int nPriority);

void func_001BAB30(void)
{
    func_001BA9F8(1, 0xFFFF);
}
