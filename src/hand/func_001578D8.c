/* func_001578D8 (0x1578D8): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001577A0(__initialize_p = 1, __priority = 0xFFFF). */
void func_001577A0(int fInitialize, int nPriority);

void func_001578D8(void)
{
    func_001577A0(1, 0xFFFF);
}
