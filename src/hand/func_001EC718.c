/* func_001EC718 (called by 0x1ED960 / 0x1EE7B0): a deferred copy carried out - {cb, the source, the destination}
 * (CopyAb). */
typedef struct COPY {
    /* 0x0 */ unsigned int cb;
    /* 0x4 */ void *pvSrc;
    /* 0x8 */ void *pvDst;
} COPY;

void CopyAb__FPvT0Ui(void *pvDst, void *pvSrc, unsigned int cb);

void func_001EC718(COPY *pcopy)
{
    CopyAb__FPvT0Ui(pcopy->pvDst, pcopy->pvSrc, pcopy->cb);
}
