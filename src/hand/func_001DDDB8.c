/* A screen string (SafeHouse shop.cpp id 0x51B, orig 0x001DDDB8): the current episode's name localized. */
struct SW;
extern struct SW g_sw;
char *func_0013E368(struct SW *psw, int id);   /* the world's localized string */
int func_001DDD40(int iepisode);               /* the episode's text id */
int func_00210AE0(void);                       /* the current episode */
char *strcpy(char *, const char *);

void func_001DDDB8(char *pch)
{
    strcpy(pch, func_0013E368(&g_sw, func_001DDD40(func_00210AE0())));
}
