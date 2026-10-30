/* func_001EE958 (0x1EE958): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001EE820(__initialize_p = 1, __priority = 0xFFFF). */
void func_001EE820(int fInitialize, int nPriority);

void func_001EE958(void)
{
    func_001EE820(1, 0xFFFF);
}
