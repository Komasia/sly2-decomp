/* func_00132550 (0x132550): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00132418(__initialize_p = 1, __priority = 0xFFFF). */
void func_00132418(int fInitialize, int nPriority);

void func_00132550(void)
{
    func_00132418(1, 0xFFFF);
}
