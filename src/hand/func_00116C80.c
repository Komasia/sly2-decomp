/* func_00116C80 (0x116C80): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_00116B30(__initialize_p = 1, __priority = 0xFFFF). */
void func_00116B30(int fInitialize, int nPriority);

void func_00116C80(void)
{
    func_00116B30(1, 0xFFFF);
}
