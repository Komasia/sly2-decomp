/* class: CID_71, the command lists (SafeHouse scptai.cpp loader methods): op 0xF with an oid and a word at +0x8. */
struct CMD {
    /* 0x0 */ char pad0[8];
    /* 0x8 */ int n8;
};
struct CMDLIST;
struct CMD *PcmdAppend__FP7CMDLISTi3OID(struct CMDLIST *pcmdlist, int op, int oid);

void func_00170DD0(struct CMDLIST *pcmdlist, int oid, int n)
{
    PcmdAppend__FP7CMDLISTi3OID(pcmdlist, 0xF, oid)->n8 = n;
}
