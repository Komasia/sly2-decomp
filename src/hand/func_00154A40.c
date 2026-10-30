/* func_00154A40 (0x154A40): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00154908(__initialize_p = 1, __priority = 0xFFFF). */
void func_00154908(int fInitialize, int nPriority);

void func_00154A40(void)
{
    func_00154908(1, 0xFFFF);
}
