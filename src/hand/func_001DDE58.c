/* A screen string (SafeHouse shop.cpp id 0x51C, orig 0x1DDE58): the shop's job's text +0x6C localized, when there is a
 * job. */
struct SW;
struct JOB {
    /* 0x00 */ char pad0[0x6c];
    /* 0x6c */ int idText;
};
extern struct SW g_sw;
extern struct JOB *D_003DA4D0;   /* the shop's job */
char *func_0013E368(struct SW *psw, int id);   /* the world's localized string */
char *strcpy(char *, const char *);

void func_001DDE58(char *pch)
{
    if (D_003DA4D0 != 0) {
        strcpy(pch, func_0013E368(&g_sw, D_003DA4D0->idText));
    }
}
