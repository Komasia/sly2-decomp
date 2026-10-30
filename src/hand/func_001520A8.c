/* func_001520A8 (0x1520A8): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00151F70(__initialize_p = 1, __priority = 0xFFFF). */
void func_00151F70(int fInitialize, int nPriority);

void func_001520A8(void)
{
    func_00151F70(1, 0xFFFF);
}
