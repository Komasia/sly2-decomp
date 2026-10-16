// Complete formatter WIP with the actual52-byte TFT record.
struct OSTRM { char pad[0x10]; int cchWritten; };
struct TFT {int fLeft,fPlus,fSpace,fPrefix,fZero,fPrec0,width,precision,cbits,matrixRows,vectorColumns;unsigned char conversion;int fUpper;};
extern "C" char *func_0021EDF8(char *p, int ch);
extern "C" int func_0021ED28(char *p);
extern "C" int func_0020D660(OSTRM *postrm, char *pb, int cb);
int CchParsePchzTft(char *pchz, TFT *ptft, char **ppv);
void WriteTft(TFT *ptft, OSTRM *postrm, char **ppv, char *pchz, int cch);

int CchOstrmPrintf(OSTRM *postrm, char *pchzFormat, char *pv)
{
    TFT tft;
    if (*(unsigned char *)pchzFormat) do {
        char *pchz = func_0021EDF8(pchzFormat, '%');
        int cch = pchz - pchzFormat;
        if (!pchz) {
            cch = func_0021ED28(pchzFormat);
            pchz = pchzFormat + cch;
        }
        if (cch != 0) {
            if (func_0020D660(postrm, pchzFormat, cch) < cch)
                break;
        }
        pchzFormat = pchz;
        if (*(unsigned char *)pchzFormat == '%') {
            int cchFmt = CchParsePchzTft(pchzFormat, &tft, &pv);
            WriteTft(&tft, postrm, &pv, pchzFormat, cchFmt);
            pchzFormat += cchFmt;
        }
    } while (*(unsigned char *)pchzFormat);
    return postrm->cchWritten;
}
