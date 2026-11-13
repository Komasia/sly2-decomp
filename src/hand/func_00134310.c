/* The larger of two overlap kinds (SafeHouse: "std::max(kind, ...) // 0x134310" in the OverlapKind* callers). */
int func_00134310(int kind, int kindOther)
{
    return kindOther >= kind ? kindOther : kind;
}
