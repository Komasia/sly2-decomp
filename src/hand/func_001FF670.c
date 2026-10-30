/* func_001FF670 (0x1FF670): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001FF538(__initialize_p = 1, __priority = 0xFFFF). */
void func_001FF538(int fInitialize, int nPriority);

void func_001FF670(void)
{
    func_001FF538(1, 0xFFFF);
}
