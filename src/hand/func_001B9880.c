/* class: MURRAY (SafeHouse gang.cpp: option 939, EOPID 1051 -> 0x1B9880, the Bentley toss: Murray's state 15). */
struct MURRAY;
void func_001B6078(struct MURRAY *pmurray, int state, int n);   /* SafeHouse: SetMurrayState */

void func_001B9880(struct MURRAY *pmurray, int n1, int n2)
{
    func_001B6078(pmurray, 15, n2);
}
