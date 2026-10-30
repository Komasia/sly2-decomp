/* func_001B4418 (0x1B4418): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001B42D0(__initialize_p = 1, __priority = 0xFFFF). */
void func_001B42D0(int fInitialize, int nPriority);

void func_001B4418(void)
{
    func_001B42D0(1, 0xFFFF);
}
