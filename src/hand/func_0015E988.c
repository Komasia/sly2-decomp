struct E { struct E *next; int x; int pad[3]; };
extern struct E D_002BAAE8[];
// name: Sly 1 find.c FIsCidDerivedFrom (walks the class descriptor chain 0x2BAAE8); SafeHouse cls.h names 0x15E988
int FIsCidDerivedFrom__F3CIDT0(int i, int x)
{
    struct E *p;
    for (p = &D_002BAAE8[i]; p; p = p->next)
        if (p->x == x)
            return 1;
    return 0;
}
