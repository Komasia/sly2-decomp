/* class: CID_71, the command lists (SafeHouse scptai.cpp loader methods): op 5 without an oid, a float at +0x8. */
struct CMD {
    /* 0x0 */ char pad0[8];
    /* 0x8 */ float g8;
};
struct CMDLIST;
struct CMD *PcmdAppend__FP7CMDLISTi3OID(struct CMDLIST *pcmdlist, int op, int oid);

void func_00170C20(struct CMDLIST *pcmdlist, float g)
{
    PcmdAppend__FP7CMDLISTi3OID(pcmdlist, 5, -1)->g8 = g;
}
