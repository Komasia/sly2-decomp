/* class: CID_71, the command lists (SafeHouse scptai.cpp loader methods): op 12 without an oid. */
struct CMD;
struct CMDLIST;
struct CMD *PcmdAppend__FP7CMDLISTi3OID(struct CMDLIST *pcmdlist, int op, int oid);

void func_00170D50(struct CMDLIST *pcmdlist, int n1, int n2)
{
    PcmdAppend__FP7CMDLISTi3OID(pcmdlist, 12, -1);
}
