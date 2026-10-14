struct S { char pad[0x204]; int f204; char pad2[0x13D0-0x208]; int n; int reserved; int m; };
int func_00143C78(struct S *p);
#define FIELD_OFFSET(t,m) ((unsigned int)&(((struct t*)0x10000)->m)-0x10000)
typedef char S_flag_Offset[FIELD_OFFSET(S,f204)==0x204?1:-1];
typedef char S_state_Offset[FIELD_OFFSET(S,n)==0x13D0?1:-1];
typedef char S_mode_Offset[FIELD_OFFSET(S,m)==0x13D8?1:-1];
typedef char S_PrefixSize[sizeof(struct S)==0x13DC?1:-1];
int func_001B8368(struct S *p)
{
    int result;
    if (p->f204) return 0;
    if (p->m == 1 || p->n != 20)
        result = func_00143C78(p);
    else
        result = 0;
    return result;
}
