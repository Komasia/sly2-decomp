struct GM { unsigned short a; unsigned short b; };
extern struct GM D_002C36A0[];
extern struct GM D_002C3728[];
unsigned short FUN_001b5b58(unsigned char ch)
{
    int i = 0;
    int j;
    if ((unsigned)(ch - 0x20) < 0x10) i = 1;
    else if ((unsigned)(ch - 0x30) < 10) j = 0;
    else if ((unsigned)(ch - 0x3A) < 7) i = 0xB;
    else if ((unsigned)(ch - 0x41) < 0x1A) j = 1;
    else if ((unsigned)(ch - 0x5B) < 6) i = 0x25;
    else if ((unsigned)(ch - 0x61) < 0x1A) j = 2;
    else if ((unsigned)(ch - 0x7B) < 4) i = 0x3F;
    else return 0;
    if (i == 0) { return D_002C3728[j].a + ch - D_002C3728[j].b; } { int k = i + 0x1F; return D_002C36A0[ch - k].a; }
}
