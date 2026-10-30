/* func_001B0B58 (0x1B0B58): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001B0A20(__initialize_p = 1, __priority = 0xFFFF). */
void func_001B0A20(int fInitialize, int nPriority);

void func_001B0B58(void)
{
    func_001B0A20(1, 0xFFFF);
}
