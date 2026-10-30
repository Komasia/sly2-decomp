/* func_001571E0 (0x1571E0): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001570A8(__initialize_p = 1, __priority = 0xFFFF). */
void func_001570A8(int fInitialize, int nPriority);

void func_001571E0(void)
{
    func_001570A8(1, 0xFFFF);
}
