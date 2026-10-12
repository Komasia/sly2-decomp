int func_001B0078(void);
int func_001B0108(void)
{
    switch (func_001B0078()) {
    case 0x19: case 0x1E: case 0x1F:
        return 1;
    }
    return 0;
}
