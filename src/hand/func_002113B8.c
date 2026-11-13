/* A screen string generator (SafeHouse screenrt.cpp, orig 0x002113B8 (0x2F0): the prompt's buttons, 0x227940 on the
 * subtitle state D_004435F0). */
extern char D_004435F0[];
void func_00227940(void *p, char *pch);

void func_002113B8(char *pch)
{
    func_00227940(D_004435F0, pch);
}
