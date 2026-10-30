/* func_001B4708 (0x1B4708): g++ global-constructor entry of its translation unit: runs the unit's static
 * initialisation, func_001B45D0(__initialize_p = 1, __priority = 0xFFFF). */
void func_001B45D0(int fInitialize, int nPriority);

void func_001B4708(void)
{
    func_001B45D0(1, 0xFFFF);
}
