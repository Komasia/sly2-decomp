/* PcmdAppend: a new command (from the slot heap D_003E1548) with its op and oid appended to a command list's
 * commands (+0x50). Source: SafeHouse port (ai.cpp). */
struct CMD {
    /* 0x0 */ int op;    /* field: SafeHouse port */
    /* 0x4 */ int oid;   /* field: SafeHouse port */
};
struct CMDLIST {
    /* 0x00 */ char pad0[0x50];
    /* 0x50 */ char slcmd[8];   /* the commands' list */
};
extern char D_003E1548[];   /* the commands' slot heap */
void *func_0011CCC0(void *pslotheap);    /* a slot heap's new slot */
void func_0011A070(void *psl, void *pv); /* appended to a list */

// name: SafeHouse port (PcmdAppend)
struct CMD *PcmdAppend__FP7CMDLISTi3OID(struct CMDLIST *pcmdlist, int op, int oid)
{
    struct CMD *pcmd = (struct CMD *)func_0011CCC0(D_003E1548);
    pcmd->op = op;
    pcmd->oid = oid;
    func_0011A070(pcmdlist->slcmd, pcmd);
    return pcmd;
}
