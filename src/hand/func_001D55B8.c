/* FVibrationEnabled (SafeHouse rumble.h, orig 0x1D55B8): is controller vibration on? Option On -> yes; boot (0) or
 * Off -> no; title shown (1) -> the saved progress record's fNoVibration flag decides. */
typedef struct CRef { int tagk; int tag; } CRef;
extern int D_002C2D8C;          /* the vibration option (SafeHouse g_vibrationSetting) */
extern void *D_003E0FD8;        /* the progress record */
extern char D_003D4A60[];       /* the progress key of the fNoVibration flag */
void NProgress(CRef *pref, void *pvRecord, char *pchzKey);
void Decref(CRef *pref) asm("Decref__4CRef");

#define VIBRATION_Boot 0
#define VIBRATION_Title 1
#define VIBRATION_On 2
#define VIBRATION_Off 3

// name: SafeHouse port (FVibrationEnabled)
int FVibrationEnabled__Fv(void)
{
    switch (D_002C2D8C) {
    case VIBRATION_On:
        return 1;
    case VIBRATION_Boot:
    case VIBRATION_Off:
        return 0;
    case VIBRATION_Title:
    default: {
        CRef refNoVibration;
        int fNoVibration;
        NProgress(&refNoVibration, D_003E0FD8, D_003D4A60);
        fNoVibration = refNoVibration.tag;
        Decref(&refNoVibration);
        return fNoVibration ^ 1;
    }
    }
}
