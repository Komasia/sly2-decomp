/* func_00128B40 (0x128B40): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00128A00(__initialize_p = 1, __priority = 0xFFFF). */
void func_00128A00(int fInitialize, int nPriority);

void func_00128B40(void)
{
    func_00128A00(1, 0xFFFF);
}
