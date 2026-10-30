/* func_00166900 (0x166900): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001667C8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001667C8(int fInitialize, int nPriority);

void func_00166900(void)
{
    func_001667C8(1, 0xFFFF);
}
