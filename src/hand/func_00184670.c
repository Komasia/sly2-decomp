int func_00132B10(void *p, int n);
void *func_00184670(char *p)
{
    if (!p) return 0;
    if (func_00132B10(p, 0x58)) return p + 0x150;
    if (func_00132B10(p, 0x1B)) return p + 0x130;
    if (func_00132B10(p, 0x22)) return p + 0xE0;
    if (func_00132B10(p, 0xC)) return p + 0x190;
    if (func_00132B10(p, 0x23)) return p + 0xE0;
    if (func_00132B10(p, 0x13)) return p + 0x100;
    if (func_00132B10(p, 0xB)) return p + 0x190;
    if (func_00132B10(p, 0xD)) return p + 0x190;
    if (func_00132B10(p, 0x27)) return p + 0xE0;
    return 0;
}
