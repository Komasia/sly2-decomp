/* class: CID_71, the command lists (SafeHouse scptai.cpp: the loader methods, EOPIDs 595..612, each append a command
 * (PcmdAppend) with its arguments): op 0 with an oid. */
struct CMD;
struct CMDLIST;
struct CMD *PcmdAppend__FP7CMDLISTi3OID(struct CMDLIST *pcmdlist, int op, int oid);

void func_00170B40(struct CMDLIST *pcmdlist, int oid)
{
    PcmdAppend__FP7CMDLISTi3OID(pcmdlist, 0, oid);
}
