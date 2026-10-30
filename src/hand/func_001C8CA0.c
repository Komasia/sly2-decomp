/* func_001C8CA0 (0x1C8CA0): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001C8B68(__initialize_p = 1, __priority = 0xFFFF). */
void func_001C8B68(int fInitialize, int nPriority);

void func_001C8CA0(void)
{
    func_001C8B68(1, 0xFFFF);
}
