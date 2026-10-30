/* func_00117010 (0x117010): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00116ED8(__initialize_p = 1, __priority = 0xFFFF). */
void func_00116ED8(int fInitialize, int nPriority);

void func_00117010(void)
{
    func_00116ED8(1, 0xFFFF);
}
