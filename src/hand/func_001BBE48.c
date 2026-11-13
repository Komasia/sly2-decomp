/* class: the breakables (SafeHouse breakable.cpp, orig 0x001BBE48: broken - no valid current event, 0x1BBE18). */
struct BREAKABLE;
int func_001BBE18(struct BREAKABLE *pbrk);

int func_001BBE48(struct BREAKABLE *pbrk)
{
    return func_001BBE18(pbrk) == 0;
}
