/* func_00201600 (0x201600): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_002014C8(__initialize_p = 1, __priority = 0xFFFF). */
void func_002014C8(int fInitialize, int nPriority);

void func_00201600(void)
{
    func_002014C8(1, 0xFFFF);
}
