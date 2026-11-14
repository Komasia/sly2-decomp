// Complete formatter WIP with the actual52-byte TFT record.
struct OSTRM { char pad[0x10]; int cchWritten; };
struct TFT {int fLeft,fPlus,fSpace,fPrefix,fZero,fPrec0,width,precision,cbits,matrixRows,vectorColumns;unsigned char conversion;int fUpper;};
extern "C" char *strchr(char *p, int ch);
extern "C" int s1_strlen(char *p) asm("strlen");
extern "C" int CbWrite(OSTRM *postrm, char *pb, int cb) asm("CbWrite__5OSTRMPvi");
int CchParsePchzTft(char *pchz, TFT *ptft, char **ppv);
void WriteTft(TFT *ptft, OSTRM *postrm, char **ppv, char *pchz, int cch);

int CchOstrmPrintf(OSTRM *postrm, char *pchzFormat, char *pv)
{
    TFT tft;
    if (*(unsigned char *)pchzFormat) do {
        char *pchz = strchr(pchzFormat, '%');
        int cch = pchz - pchzFormat;
        if (!pchz) {
            cch = s1_strlen(pchzFormat);
            pchz = pchzFormat + cch;
        }
        if (cch != 0) {
            if (CbWrite(postrm, pchzFormat, cch) < cch)
                break;
            pchzFormat = pchz;
        }
        if (*(unsigned char *)pchzFormat == '%') {
            int cchFmt = CchParsePchzTft(pchzFormat, &tft, &pv);
            WriteTft(&tft, postrm, &pv, pchzFormat, cchFmt);
            pchzFormat += cchFmt;
        }
    } while (*(unsigned char *)pchzFormat);
    return postrm->cchWritten;
}
