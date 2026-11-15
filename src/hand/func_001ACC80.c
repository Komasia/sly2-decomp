/* NCardPrompt (0x1ACC80): the kind of the memory card prompt's message (+0x40): 1 a notice (OK), 2 a question
 * (yes / no), 0 none. SafeHouse menu.cpp. */
struct S { char pad[0x40]; int msg; };
// name: SafeHouse port (NCardPrompt)
int NCardPrompt__FPv(struct S *pprompt)
{
    switch (pprompt->msg) {
    case 0x11: case 0x14: case 0x17: case 0x18: case 0x1B: case 0x1D: case 0x22: case 0x23: case 0x24: case 0x2E:
        return 1;
    case 0x12: case 0x15: case 0x1C: case 0x20:
        return 2;
    }
    return 0;
}
