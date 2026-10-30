/* func_001C9920 (0x1C9920): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001C9688(__initialize_p = 1, __priority = 0xFFFF). */
void func_001C9688(int fInitialize, int nPriority);

void func_001C9920(void)
{
    func_001C9688(1, 0xFFFF);
}
