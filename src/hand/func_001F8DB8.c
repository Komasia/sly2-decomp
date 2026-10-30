/* func_001F8DB8 (0x1F8DB8): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001F8C40(__initialize_p = 1, __priority = 0xFFFF). */
void func_001F8C40(int fInitialize, int nPriority);

void func_001F8DB8(void)
{
    func_001F8C40(1, 0xFFFF);
}
