/* FUN_0018b780 (name taken from a Sly 1 address): fill a save-file entry from a memory card directory entry
 * (sceMcTblGetDir, as returned by sceMcGetDir): the name, the size, the attributes squeezed into 8 flag bits, and
 * the creation and modification dates (CompareSaves orders entries by the modification date). */
typedef struct sceMcStDateTime {
    unsigned char Resv2;
    unsigned char Sec;
    unsigned char Min;
    unsigned char Hour;
    unsigned char Day;
    unsigned char Month;
    unsigned short Year;
} sceMcStDateTime;

typedef struct sceMcTblGetDir {
    /* 0x00 */ sceMcStDateTime _Create;
    /* 0x08 */ sceMcStDateTime _Modify;
    /* 0x10 */ unsigned int FileSizeByte;
    /* 0x14 */ unsigned short AttrFile;
    /* 0x16 */ unsigned short Reserve1;
    /* 0x18 */ unsigned int Reserve2;
    /* 0x1c */ unsigned int PdaAplNo;
    /* 0x20 */ unsigned char EntryName[32];
} sceMcTblGetDir;

/* the game's date: month, day, year, then the time */
typedef struct MCDATE {
    unsigned char bMonth;
    unsigned char bDay;
    unsigned short nYear;
    unsigned char bHour;
    unsigned char bMinute;
    unsigned char bSecond;
    unsigned char bPad;
} MCDATE;

typedef struct MCENTRY {
    /* 0x00 */ char achName[0x44];
    /* 0x44 */ int cb;
    /* 0x48 */ unsigned int fReadable : 1;
               unsigned int fWritable : 1;
               unsigned int fExecutable : 1;
               unsigned int fCopyProtected : 1;
               unsigned int fSubdir : 1;
               unsigned int fClosed : 1;
               unsigned int fPocketStation : 1;
               unsigned int fPlayStation : 1;
               unsigned int pad49 : 8;
    /* 0x4a */ MCDATE dateCreate;
    /* 0x52 */ MCDATE dateModify;
    /* 0x5a */ unsigned char pad[2];
} MCENTRY;   /* 0x5c bytes */

int memset(void *pv, int b, int cb);
int strcpy(void *pchDst, int pchSrc);

void FUN_0018b780(sceMcTblGetDir *pdir, MCENTRY *pentry)
{
    memset(pentry, 0, 0x5C);
    strcpy(pentry, (int)pdir->EntryName);
    pentry->cb = pdir->FileSizeByte;
    if (pdir->AttrFile & 0x1) pentry->fReadable = 1;
    if (pdir->AttrFile & 0x2) pentry->fWritable = 1;
    if (pdir->AttrFile & 0x4) pentry->fExecutable = 1;
    if (pdir->AttrFile & 0x8) pentry->fCopyProtected = 1;
    if (pdir->AttrFile & 0x20) pentry->fSubdir = 1;
    if (pdir->AttrFile & 0x80) pentry->fClosed = 1;
    if (pdir->AttrFile & 0x800) pentry->fPocketStation = 1;
    if (pdir->AttrFile & 0x1000) pentry->fPlayStation = 1;
    pentry->dateCreate.bMonth = pdir->_Create.Month;
    pentry->dateCreate.bDay = pdir->_Create.Day;
    pentry->dateCreate.nYear = pdir->_Create.Year;
    pentry->dateCreate.bHour = pdir->_Create.Hour;
    pentry->dateCreate.bMinute = pdir->_Create.Min;
    pentry->dateCreate.bSecond = pdir->_Create.Sec;
    pentry->dateModify.bMonth = pdir->_Modify.Month;
    pentry->dateModify.bDay = pdir->_Modify.Day;
    pentry->dateModify.nYear = pdir->_Modify.Year;
    pentry->dateModify.bHour = pdir->_Modify.Hour;
    pentry->dateModify.bMinute = pdir->_Modify.Min;
    pentry->dateModify.bSecond = pdir->_Modify.Sec;
}
