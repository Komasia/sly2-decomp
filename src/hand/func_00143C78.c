int func_00143C78(char *p)
{
    if (*(int *)(p + 0x204)) return 0;
    switch (*(int *)(p + 0x4C8)) {
    case 3:
    case 4:
        return 4;
    }
    if (*(int *)(p + 0x2DC) != -1) return 1;
    switch (*(int *)(p + 0xDF4)) {
    case -1:
    case 0:
    case 6:
        return 7;
    case 4:
    case 7:
    case 8:
    case 12:
        return 1;
    }
    return 0;
}
