/* func_001D1350 (0x1D1350): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001D1218(__initialize_p = 1, __priority = 0xFFFF). */
void func_001D1218(int fInitialize, int nPriority);

void func_001D1350(void)
{
    func_001D1218(1, 0xFFFF);
}
