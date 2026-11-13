/* A save slot validated (SafeHouse frontend.cpp: 0x1AC570 -> 0x1D7C80 on the read slot D_003E0EA8). */
extern char D_003E0EA8[];
void ValidateGameSave__FPvT0(void *pv);

int func_001AC570(void)
{
    ValidateGameSave__FPvT0(D_003E0EA8);
    return 0;
}
