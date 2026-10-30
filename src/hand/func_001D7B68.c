/* func_001D7B68 (0x1D7B68): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001D7A30(__initialize_p = 1, __priority = 0xFFFF). */
void func_001D7A30(int fInitialize, int nPriority);

void func_001D7B68(void)
{
    func_001D7A30(1, 0xFFFF);
}
