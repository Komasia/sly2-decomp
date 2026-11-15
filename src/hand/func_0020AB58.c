/* func_0020AB58 (0x20AB58): clears the guard's action oids and objects. */
#define OFS_GUARD_COIDACTION 0xED8
#define OFS_GUARD_CPLOACTION 0xEFC
void func_0020AB58(char *pguard) { *(int *)(pguard + OFS_GUARD_COIDACTION) = 0; *(int *)(pguard + OFS_GUARD_CPLOACTION) = 0; }
