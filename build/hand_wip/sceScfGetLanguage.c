// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
typedef struct {
  unsigned int spdifMode:1;
  unsigned int screenType:2;
  unsigned int videoOutput:1;
  unsigned int japLanguage:1;
  unsigned int ps1drvConfig:8;
  unsigned int version:3;
  unsigned int language:5;
  unsigned int timezoneOffset:11;
} sceOsdConfigParam;
void func_00234AD0(sceOsdConfigParam *p);
int func_0024A820(void);
extern unsigned char D_002C8374[];
int sceScfGetLanguage(void)
{
  sceOsdConfigParam cp;
  func_00234AD0(&cp);
  if (func_0024A820())
    return D_002C8374[0];
  func_00234AD0(&cp);
  if (cp.version != 0)
    return cp.language;
  return cp.japLanguage;
}
