/* func_001CBE90 (0x1CBE90): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001CBD58(__initialize_p = 1, __priority = 0xFFFF). */
void func_001CBD58(int fInitialize, int nPriority);

void func_001CBE90(void)
{
    func_001CBD58(1, 0xFFFF);
}
