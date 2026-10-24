// func_001FD0E8 LoadSoundSectionFromBrx (sound bank record + dialogue / music stream records of a level)
typedef unsigned char    uchar;
typedef unsigned short   ushort;
typedef unsigned int     uint;
typedef uchar byte;
typedef unsigned long ulong;
struct SNDMGR;
class CBinaryStreamBase
{
public:
    int m_grfbis;
    byte *m_pb;
    int m_cb;
    int m_ibStream;
    byte *m_pbRaw;
    int m_cbRaw;
    int m_grfDecomp;
    int m_cbSpillOver;
    int m_unk20;
    byte *m_abWindow;
    int m_unk28;
    int m_unk2c;
};
class CBinaryInputStream : public CBinaryStreamBase
{
public:
    int m_cbSpool;
    byte *m_abSpool;
    int m_fd;
    int m_cbDone;
    int m_cbRequest;
    int m_cbRemaining;
    int m_cbRetry;
    int m_isector;
    int m_cbuf;
    int m_cbufFill;
    int m_icbufRead;
    int m_icbufWrite;
    void Read(int cb, void *pv);
    uchar U8Read();
    char S8Read();
    short S16Read();
    int S32Read();
    float F32Read();
    void ReadFileRecord(void *pv);
};
struct FILEREC
{
    uint aw[16];
};
struct SWALLOC
{
    int cb;
    int cbAlign;
};
void *PvAllocSwImpl(SWALLOC *pswalloc);
void *PvAllocSwClearImpl(SWALLOC *pswalloc);
inline void *PvAllocSwLoad(int cb, int cbAlign)
{
    SWALLOC swalloc;
    swalloc.cb = cb;
    swalloc.cbAlign = cbAlign;
    return PvAllocSwImpl(&swalloc);
}
inline void *PvAllocSwClearLoad(int cb, int cbAlign)
{
    SWALLOC swalloc;
    swalloc.cb = cb;
    swalloc.cbAlign = cbAlign;
    return PvAllocSwClearImpl(&swalloc);
}
struct STREAMSND;
static inline SWALLOC *PswallocOf(SWALLOC *p) { return p; }
struct SNDSTREAM
{
    FILEREC rec;
    int id;
    SNDSTREAM *psndstreamNext;
    int nUnk48;
    int nUnk4C;
    float gUnk50;
    int cpair;
    ulong *apair;
};
struct SNDFILE
{
    FILEREC rec;
    int id;
    SNDFILE *psndfileNext;
};
struct SNDMGR
{
    byte ab[0x18];
    int csfx;
    byte abUnk1c[0x8c];
    FILEREC rec;
    void *pbank;
    SNDSTREAM *psndstreamFirst;
    SNDFILE *psndfileFirst;
    FILEREC *precAmbience;
    int csnd;
    int *anKind;
    int *aisnd;
    byte abUnk104[0xCC];
    int cUnk1D0;
    int anUnk1D4[6];
    byte abUnk1EC[0x3C];
    STREAMSND *psndAmbience;
};
extern int D_002E1E54;
extern "C" void func_002321B8(void *);
extern "C" int func_00231C48(void);
extern "C" void *func_002333B4(void *, int, uint);
extern "C" STREAMSND *func_001FC138(FILEREC *, int);
extern "C" void func_00259B48(void *, STREAMSND *);
inline int FSameFileId(FILEREC *prec, FILEREC *precOther)
{
    if (prec == precOther)
        return 1;
    if (prec == 0 || precOther == 0)
        return 0;
    return (prec->aw[2] ^ prec->aw[14]) == (precOther->aw[2] ^ precOther->aw[14]);
}
extern "C" void LoadSoundSectionFromBrx(SNDMGR *psndmgr, CBinaryInputStream *pbis) __asm__("func_001FD0E8");
extern "C" void LoadSoundSectionFromBrx(SNDMGR *psndmgr, CBinaryInputStream *pbis)
{
    FILEREC rec;
    SWALLOC swalloc;
    pbis->ReadFileRecord(&rec);
    if (!FSameFileId(&rec, &psndmgr->rec))
    {
        psndmgr->rec = rec;
        if (psndmgr->pbank)
        {
            func_002321B8(psndmgr->pbank);
            while (func_00231C48())
                ;
            psndmgr->pbank = 0;
        }
    }
    int *panUnk = psndmgr->anUnk1D4;
    int i;
    psndmgr->csnd = pbis->S16Read();
    swalloc.cb = psndmgr->csnd * sizeof(int);
    swalloc.cbAlign = 0x10;
    psndmgr->anKind = (int *)PvAllocSwClearImpl(&swalloc);
    for (i = 0; i < psndmgr->csnd; i++)
    {
        int *pn = &psndmgr->anKind[i];
        *pn = pbis->S8Read();
    }
    psndmgr->csfx = pbis->S16Read();
    swalloc.cb = psndmgr->csfx * sizeof(int);
    swalloc.cbAlign = 0x10;
    psndmgr->aisnd = (int *)PvAllocSwImpl(&swalloc);
    func_002333B4(psndmgr->aisnd, -1, psndmgr->csfx * sizeof(int));
    int j;
    for (j = 0; j < psndmgr->csnd; j++)
        psndmgr->aisnd[pbis->S16Read()] = j;
    psndmgr->cUnk1D0 = pbis->S16Read();
    if (psndmgr->cUnk1D0 > 0)
    {
        swalloc.cb = sizeof(FILEREC);
    swalloc.cbAlign = 0x10;
    psndmgr->precAmbience = (FILEREC *)PvAllocSwClearImpl(&swalloc);
        pbis->ReadFileRecord(psndmgr->precAmbience);
        STREAMSND *psnd = func_001FC138(psndmgr->precAmbience, 4);
        func_00259B48(&psndmgr->psndAmbience, psnd);
    }
    func_002333B4(panUnk, -1, sizeof(psndmgr->anUnk1D4));
    for (i = 0; i < psndmgr->cUnk1D0; i++)
        panUnk[i] = pbis->S16Read();
    int clang = pbis->U8Read();
    int ilangMatch = 0;
    for (int ilang = 0; ilang < clang; ilang++)
    {
        if (pbis->U8Read() == D_002E1E54)
            ilangMatch = ilang;
    }
    int cstream = pbis->S32Read();
    swalloc.cb = cstream * sizeof(SNDSTREAM);
    swalloc.cbAlign = 0x10;
    SNDSTREAM *astream = (SNDSTREAM *)PvAllocSwClearImpl(&swalloc);
    for (i = 0; i < cstream; i++)
    {
        SNDSTREAM *pstream = &astream[i];
        pstream->id = pbis->S16Read();
        pstream->nUnk48 = pbis->S16Read();
        for (int ilang = 0; ilang < clang; ilang++)
        {
            FILEREC recLang;
            pbis->ReadFileRecord(&recLang);
            int nUnk4C = pbis->S8Read();
            float gUnk50 = pbis->F32Read();
            if (ilang == ilangMatch)
            {
                pstream->rec = recLang;
                pstream->nUnk4C = nUnk4C;
                pstream->gUnk50 = gUnk50;
            }
        }
        pstream->cpair = pbis->S32Read();
        swalloc.cb = pstream->cpair * 8;
        swalloc.cbAlign = 0x10;
        pstream->apair = (ulong *)PvAllocSwImpl(&swalloc);
        pbis->Read(pstream->cpair * 8, pstream->apair);
        pstream->psndstreamNext = psndmgr->psndstreamFirst;
        psndmgr->psndstreamFirst = pstream;
    }
    int cfile = pbis->S32Read();
    swalloc.cb = cfile * sizeof(SNDFILE);
    swalloc.cbAlign = 0x10;
    SNDFILE *afile = (SNDFILE *)PvAllocSwClearImpl(&swalloc);
    for (i = 0; i < cfile; i++)
    {
        SNDFILE *pfile = &afile[i];
        pfile->id = pbis->S16Read();
        pbis->ReadFileRecord(pfile);
        pfile->psndfileNext = psndmgr->psndfileFirst;
        psndmgr->psndfileFirst = pfile;
    }
}
