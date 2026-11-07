int KindDataAccess__FP4MENU(void);
int func_001B0108(void)
{
    switch (KindDataAccess__FP4MENU()) {
    case 0x19: case 0x1E: case 0x1F:
        return 1;
    }
    return 0;
}
