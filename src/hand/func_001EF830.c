/* func_001EF830 (0x1EF830): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001EF6F8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001EF6F8(int fInitialize, int nPriority);

void func_001EF830(void)
{
    func_001EF6F8(1, 0xFFFF);
}
