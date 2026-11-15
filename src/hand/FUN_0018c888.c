/* FUN_0018c888 (0x1ABE78): lists a card directory: up to 18 entries (0x25 above) of path (kept in D_002E6500;
 * null: continue the last listing) read by sceMcGetDir into D_002E6080, then each converted to a save directory entry
 * (0x1AA9B8 = FUN_0018b780); a path over 64 characters is error 0xD. */
typedef struct { char a[0x40]; } ENT;
typedef struct { char a[0x5C]; } OUT;
extern char D_002E6500[];
extern ENT D_002E6080[];
unsigned int s1_strlen(const char *) asm("strlen");
char *s1_strcpy(char *, const char *) asm("strcpy");
void *s1_memset(void *, int, unsigned int) asm("memset");
int sceMcGetDir(int, int, char *, int, int, ENT *);
int func_001AB098(void *, int, int, int *);
void func_001AA9B8(ENT *, OUT *);

int FUN_0018c888(int *pmc, char *path, int centMax, OUT *adirent, int *pcent)
{
    int f;
    int r;
    int i;
    if (centMax > 0x12)
        return 0x25;
    if (path) {
        if (s1_strlen(path) > 0x40)
            return 0xD;
        s1_strcpy(D_002E6500, path);
        f = 0;
    } else {
        f = 1;
        path = D_002E6500;
    }
    s1_memset(D_002E6080, 0, 0x480);
    r = func_001AB098((char *)pmc + 0xFD5C, sceMcGetDir(pmc[0], pmc[1], path, f, centMax, D_002E6080), 0xD, pcent);
    if (r)
        return r;
    for (i = 0; i < *pcent; i++)
        func_001AA9B8(&D_002E6080[i], &adirent[i]);
    return 0;
}
