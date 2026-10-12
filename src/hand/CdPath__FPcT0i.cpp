extern "C" {
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
unsigned int strlen(const char *);
int sprintf(char *, const char *, ...);
}
int CpchzTokenizePath(char *pchz);
void CdPath(char *pchzOut, char *pchzIn, int fCdrom)
{
    char achPath[256];
    int c;
    int i;
    strcpy(achPath, "\\");
    strcat(achPath, pchzIn);
    c = CpchzTokenizePath(achPath);
    char *pch = achPath;
    for (i = 1; i < c; i++) {
        pch[strlen(pch)] = '\\';
    }
    sprintf(pchzOut, "%s\\%s", fCdrom ? "cdrom0:" : "", achPath);
}
