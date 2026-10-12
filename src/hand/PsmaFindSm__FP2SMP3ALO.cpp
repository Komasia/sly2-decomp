struct ALO;
struct SMA { char pad[0x14]; SMA *psmaNext; char pad2[0x10]; ALO *palo; };
struct SM { char pad[0x68]; SMA *psmaFirst; };
SMA *PsmaFindSm(SM *psm, ALO *palo)
{
    int unused[2];
    SMA *psma;
    for (psma = psm->psmaFirst; psma; psma = psma->psmaNext)
        if (psma->palo == palo) return psma;
    return 0;
}
