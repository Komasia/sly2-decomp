/* func_001E5D60 (0x1E5D60): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001E5C28(__initialize_p = 1, __priority = 0xFFFF). */
void func_001E5C28(int fInitialize, int nPriority);

void func_001E5D60(void)
{
    func_001E5C28(1, 0xFFFF);
}
