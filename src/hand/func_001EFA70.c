/* func_001EFA70 (0x1EFA70): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001EF938(__initialize_p = 1, __priority = 0xFFFF). */
void func_001EF938(int fInitialize, int nPriority);

void func_001EFA70(void)
{
    func_001EF938(1, 0xFFFF);
}
