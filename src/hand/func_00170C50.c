/* class: CID_71, the command lists (SafeHouse scptai.cpp / spawner.cpp: op 6 with an oid, {n8, nC}). */
struct CMD {
    /* 0x0 */ char pad0[8];
    /* 0x8 */ int n8;
    /* 0xc */ int nC;
};
struct CMDLIST;
struct CMD *PcmdAppend__FP7CMDLISTi3OID(struct CMDLIST *pcmdlist, int op, int oid);

void func_00170C50(struct CMDLIST *pcmdlist, int oid, int n8, int nC)
{
    struct CMD *pcmd = PcmdAppend__FP7CMDLISTi3OID(pcmdlist, 6, oid);
    pcmd->n8 = n8;
    pcmd->nC = nC;
}
