/* class: CID_71, the command lists (SafeHouse scptai.cpp loader methods, EOPIDs 595..612): op 9 with an oid. */
struct CMD;
struct CMDLIST;
struct CMD *PcmdAppend__FP7CMDLISTi3OID(struct CMDLIST *pcmdlist, int op, int oid);

void func_00170CF0(struct CMDLIST *pcmdlist, int oid)
{
    PcmdAppend__FP7CMDLISTi3OID(pcmdlist, 9, oid);
}
