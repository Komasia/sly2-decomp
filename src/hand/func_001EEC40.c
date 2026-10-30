/* func_001EEC40 (0x1EEC40): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001EEB08(__initialize_p = 1, __priority = 0xFFFF). */
void func_001EEB08(int fInitialize, int nPriority);

void func_001EEC40(void)
{
    func_001EEB08(1, 0xFFFF);
}
