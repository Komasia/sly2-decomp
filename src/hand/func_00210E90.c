/* func_00210E90 (0x210E90): g++ global-destructor entry of its translation unit: runs the unit's static destruction,
 * func_00210CF0(__initialize_p = 0, __priority = 0xFFFF). */
void func_00210CF0(int fInitialize, int nPriority);

void func_00210E90(void)
{
    func_00210CF0(0, 0xFFFF);
}
