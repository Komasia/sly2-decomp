/* func_00119D80 (0x119D80): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00119C48(__initialize_p = 1, __priority = 0xFFFF). */
void func_00119C48(int fInitialize, int nPriority);

void func_00119D80(void)
{
    func_00119C48(1, 0xFFFF);
}
