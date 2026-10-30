/* func_001B9F60 (0x1B9F60): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001B9E28(__initialize_p = 1, __priority = 0xFFFF). */
void func_001B9E28(int fInitialize, int nPriority);

void func_001B9F60(void)
{
    func_001B9E28(1, 0xFFFF);
}
