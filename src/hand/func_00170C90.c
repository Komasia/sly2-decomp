/* class: CID_71, the command lists (SafeHouse scptai.cpp: op 7, go to - +0x14 the float, +0x10 the object faced on
 * the way). */
struct CMD {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ int oidFace;
    /* 0x14 */ float g;
};
struct CMDLIST;
struct CMD *PcmdAppend__FP7CMDLISTi3OID(struct CMDLIST *pcmdlist, int op, int oid);

void func_00170C90(struct CMDLIST *pcmdlist, int oid, int oidFace, float g)
{
    struct CMD *pcmd = PcmdAppend__FP7CMDLISTi3OID(pcmdlist, 7, oid);
    pcmd->g = g;
    pcmd->oidFace = oidFace;
}
