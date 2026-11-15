/* The object an ASEGA's events act around: its own object (+0x18), else its ASEG (+0x14). SafeHouse port (asega.h). */
struct ASEGA { int pad[5]; int paseg; int palo; };
int func_00131270(struct ASEGA *pasega)
{
    if (pasega->palo)
        return pasega->palo;
    return pasega->paseg;
}
