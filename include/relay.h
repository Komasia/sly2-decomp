/* Sly 2 relays and their scripts (Sly 1 relay.c / jsg.c family).
 *
 * A RELAY is an LO holding an array of script commands (RELAYCMD, 0x50 bytes each). The script loader appends
 * the commands one at a time through PcmdNew__FP4SCPTii (appends a zeroed command); each per-kind adder (func_001E0290 ..
 * func_001E1B10) then stores the command's arguments in the payload union. When the relay fires, a JSG runs
 * the commands (NextJsgCommand, FIsJsgCommandComplete).
 *
 * Layouts, field names and the command kinds are from Lilly's Sly 2 types (src/hand/func_001E1E30.cpp and
 * func_001E3890.cpp, "ported from Lilly's personal Sly 2 decomp"). The payload union lists one member per kind
 * that carries arguments, in kind order; kinds without arguments have no member. Kind names that Lilly's enum
 * does not give are formed from the payload member name (RELAYCK_Unk<kind> where there is none).
 */
#ifndef RELAY_H
#define RELAY_H
#include "so.h"

typedef int OID;

enum RELAYCK {
    RELAYCK_BlockBegin = 0x00,
    RELAYCK_BlockEnd = 0x01,       /* closes the block a BlockBegin opened (PrunNew__FP2LOPvP3RUN counts the nesting) */
    RELAYCK_StopBlock = 0x02,
    RELAYCK_WaitBlocks = 0x03,
    RELAYCK_WaitAlarm = 0x04,
    RELAYCK_RaiseAlarm = 0x05,
    RELAYCK_StopRelay = 0x06,
    RELAYCK_SetCtlState = 0x07,
    RELAYCK_SetActor = 0x08,
    RELAYCK_Signal = 0x09,
    RELAYCK_PlayAseg = 0x0A,
    RELAYCK_FireRelay = 0x0B,
    RELAYCK_SetContext = 0x0C,
    RELAYCK_ApplySm = 0x0D,
    RELAYCK_WidgetShow = 0x0E,
    RELAYCK_WidgetHide = 0x0F,
    RELAYCK_SetClockRate = 0x10,
    RELAYCK_SetTaskState = 0x11,
    RELAYCK_HandsOff = 0x12,
    RELAYCK_Label = 0x13,
    RELAYCK_GotoLabel = 0x14,
    RELAYCK_GotoLabelIf = 0x15,
    RELAYCK_TeleportTo = 0x16,
    RELAYCK_Unk17 = 0x17,
    RELAYCK_SetTunnel = 0x18,
    RELAYCK_SetFocus = 0x19,
    RELAYCK_PipeTo = 0x1A,
    RELAYCK_Unk1B = 0x1B,
    RELAYCK_HeroState = 0x1C,
    RELAYCK_StepCmd1D = 0x1D,
    RELAYCK_StepCmd1E = 0x1E,
    RELAYCK_StepCmd1F = 0x1F,
    RELAYCK_StepCmd20 = 0x20,
    RELAYCK_StepCmd21 = 0x21,
    RELAYCK_StepCmd22 = 0x22,
    RELAYCK_Face = 0x23,
    RELAYCK_GoTo = 0x24,
    RELAYCK_Unk25 = 0x25,
    RELAYCK_Unk26 = 0x26,
    RELAYCK_FollowPath = 0x27,
    RELAYCK_WalkTo = 0x28,
    RELAYCK_StepCmd29 = 0x29,
    RELAYCK_Respawn = 0x2A,
    RELAYCK_LaunchTo = 0x2B,
    RELAYCK_AddObject = 0x2C,
    RELAYCK_RemoveObject = 0x2D,
    RELAYCK_SetPartFlag = 0x2E,
    RELAYCK_ClearPartFlag = 0x2F,
    RELAYCK_ShowPart = 0x30,
    RELAYCK_HidePart = 0x31,
    RELAYCK_Unk32 = 0x32,
    RELAYCK_Rumble = 0x33,
    RELAYCK_Explode = 0x34,
    RELAYCK_Eyes = 0x35,
    RELAYCK_Sound = 0x36,
    RELAYCK_StopSound = 0x37,
    RELAYCK_CamBlendFrom = 0x38,
    RELAYCK_CamBlendTo = 0x39,
    RELAYCK_Unk3A = 0x3A,
    RELAYCK_StartJtMode = 0x3B,
    RELAYCK_EndJtMode = 0x3C,
    RELAYCK_TweenPosObj = 0x3D,
    RELAYCK_TweenAimObj = 0x3E,
    RELAYCK_TweenTarget = 0x3F,
    RELAYCK_TweenTime = 0x40,
    RELAYCK_Unk41 = 0x41,
    RELAYCK_ButtonPrompt = 0x42,
    RELAYCK_Unk43 = 0x43,
    RELAYCK_StopLine = 0x44,
    RELAYCK_Line = 0x45,
    RELAYCK_Unk46 = 0x46,
    RELAYCK_Unk47 = 0x47,
    RELAYCK_Unk48 = 0x48,
    RELAYCK_Unk49 = 0x49,
    RELAYCK_Unk4A = 0x4A,
    RELAYCK_PlayAsegDefault = 0x4B,
    RELAYCK_StartMusic = 0x4C,
    RELAYCK_StopMusic = 0x4D,
    RELAYCK_WaitTimer = 0x4E,
    RELAYCK_Unk4F = 0x4F,
    RELAYCK_Unk50 = 0x50,
    RELAYCK_Unk51 = 0x51,
    RELAYCK_Unk52 = 0x52,
    RELAYCK_HintBox = 0x53,
    RELAYCK_ClearHintBox = 0x54,
    RELAYCK_SetSsgGoal = 0x55,
    RELAYCK_ResetStepGoal = 0x56,
    RELAYCK_Unk57 = 0x57,
    RELAYCK_Unk58 = 0x58,
    RELAYCK_Unk59 = 0x59,
    RELAYCK_Unk5A = 0x5A
};

typedef struct RELAYCMD {
    /* 0x00 */ int relayck;          /* enum RELAYCK */
    /* 0x04 */ int fAsync;           /* the script does not wait for the command to complete */
    /* 0x08 */ int unk_0x8[2];
    /* 0x10 */ union {
        int an[16];
        struct { OID oidLabel; } blockBegin;
        struct { OID oidLabel; } stopBlock;
        struct { int coid; OID aoid[4]; } waitBlocks;
        struct { int idAlarm; int fForget; } waitAlarm;
        struct { int idAlarm; OID oidRelay; } raiseAlarm;
        struct { OID oidRelay; } stopRelay;
        struct { OID oidObj; } setCtlState;
        struct { OID oidActor; } setActor;
        struct { int idSignal; } signal;
        struct { OID oidAseg; OID oidRoot; int grfapl; } playAseg;
        struct { OID oidRelay; OID oidFirer; } fireRelay;
        struct { OID oidContext; } setContext;
        struct { OID oidSm; OID oidUnk5; OID oidState; int fUnk7; } applySm;
        struct { OID oidWidget; int idLabel; } widgetShow;
        struct { OID oidWidget; } widgetHide;
        struct { float rate; } setClockRate;
        struct { OID oidTask; int nState; } setTaskState;
        struct { int fHandsOff; int grfHandsOff; } handsOff;
        struct { OID oidLabel; } label;
        struct { OID oidLabel; } gotoLabel;
        struct { OID oidLabel; int nValue; } gotoLabelIf;
        struct { OID oidWhere; int fAir; OID oidActor; } teleportTo;
        struct { OID oidTunnel; OID oidActor; } setTunnel;
        struct { OID oidFocus; OID oidActor; } setFocus;
        struct { OID oidTarget; float gTolerance; OID oidActor; } pipeTo;
        struct { OID oidActor; } unk1B;
        struct { int nUnk4; int nState; OID oidActor; } heroState;
        struct { OID oidGoal; OID oidActor; } stepCmd1D;
        struct { OID oidA; OID oidB; OID oidActor; } stepCmd1E;
        struct { OID oidGoal; OID oidActor; } stepCmd1F;
        struct { OID oidGoal; OID oidActor; } stepCmd20;
        struct { OID oidGoal; OID oidActor; } stepCmd21;
        struct { OID oidTarget; int nMode; int nUnk6; OID oidActor; } stepCmd22;
        struct { float dtWait; OID oidFace; OID oidActor; } face;
        struct { OID oidTarget; float uRun; float gArrive; OID oidActor; int idClip; int fUnk9; } goTo;
        struct { OID oidPath; int nPathMode; int nUnk6; float gUnk7; OID oidActor; int idClip; } followPath;
        struct { OID oidTarget; float gUnk5; int nUnk6; float gUnk7; OID oidActor; int idClip; } walkTo;
        struct { OID oidTarget; float gUnk5; float gArrive; OID oidActor; } stepCmd29;
        struct { OID oidSpot; int nUnk5; int nUnk6; OID oidActor; } respawn;
        struct { OID oidTarget; float gUnk5; float gUnk6; OID oidActor; } launchTo;
        struct { OID oidObj; float dtFade; } addObject;
        struct { OID oidObj; float dtFade; } removeObject;
        struct { OID oidAseg; OID oidPart; } setPartFlag;
        struct { OID oidAseg; OID oidPart; } clearPartFlag;
        struct { OID oidAseg; OID oidPart; } showPart;
        struct { OID oidAseg; OID oidPart; } hidePart;
        struct { int nUnk4; } unk32;
        struct { float dtRumble; int rumk; } rumble;
        struct { OID oidA; OID oidB; OID oidC; float dtDelay; } explode;
        struct { OID oidA; OID oidB; float dtEyes; } eyes;
        struct { int idSnd; OID oidA; int nUnk6; int nUnk7; float gUnk8; float gUnk9; float gUnk10; } sound;
        struct { int idSnd; } stopSound;
        struct { int nUnk4; } unk3A;
        struct { OID oidActor; OID oidStep; OID oidUnk6; } startJtMode;
        struct { OID oidObj; } tweenPosObj;
        struct { OID oidObj; } tweenAimObj;
        struct { float gUnk4; } tweenTime;
        struct { int grfbtn; OID oidWho; } buttonPrompt;
        struct { int nUnk4; OID oidActor; } unk43;
        struct { int idLine; int fWait; } line;
        struct { OID oidActor; int nUnk5; int nUnk6; } unk47;
        struct { OID oidActor; int nUnk5; int nUnk6; } unk48;
        struct { int nUnk4; } unk49;
        struct { float gUnk4; int nUnk5; int nUnk6; OID oidActor; } unk4A;
        struct { OID oidOther; OID oidActor; } playAsegDefault;
        struct { int idMusic; } startMusic;
        struct { int idMusic; } stopMusic;
        struct { float dtWait; } waitTimer;
        struct { OID oidActor; int nUnk5; int nUnk6; int nUnk7; int nUnk8; } unk4F;
        struct { OID oidActor; } unk50;
        struct { OID oidActor; } unk51;
        struct { float dtWait; } unk52;
        struct { int idHint; float dtHint; } hintBox;
        struct { int idHint; } clearHintBox;
        struct { OID oidStep; OID oidSsg; } setSsgGoal;
        struct { OID oidStep; OID oidUnk5; } resetStepGoal;
        struct { OID oidActor; } unk57;
        struct { OID oidShip; OID oidActor; } unk58;
        struct { OID oidShip; OID oidActor; } unk59;
        struct { OID oidShip; OID oidActor; int nUnk6; } unk5A;
    } u;
} RELAYCMD;   /* 0x50 bytes (camera kinds 0x38/0x39/0x3F also keep a qword position at +0x10) */

struct JSG;
struct ALARM;

typedef struct RELAY {
    /* 0x00 */ LO lo;
    /* 0x50 */ int crelaycmd;
    /* 0x54 */ RELAYCMD *arelaycmd;
    /* 0x58 */ int crelaycmdMax;       /* < 0: the default limit of 0x200 */
    /* 0x5c */ DL dlJsg;
    /* 0x68 */ struct JSG *pjsgSignal;  /* the script waiting in a Signal command */
    /* 0x6c */ LO *ploFirer;
    /* 0x70 */ float tFired;
    /* 0x74 */ int fFiring;
    /* 0x78 */ int fBusy;
    /* 0x7c */ int fAppendEnd;
    /* 0x80 */ int nUnk80;
    /* 0x84 */ int calarm;
    /* 0x88 */ struct ALARM *apalarm[8];
    /* 0xa8 */ int unk_0xa8[2];
} RELAY;

/* script runner of a fired relay; reference counted (cref) */
typedef struct JSG {
    /* 0x00 */ BASIC basic;
    /* 0x10 */ int cref;
    /* 0x14 */ RELAY *prelay;
    /* 0x18 */ LO *ploContext;
    /* 0x1c */ LO *ploBlock;
    /* 0x20 */ LO *ploActorDefault;
    /* 0x24 */ LO *ploActor;
    /* 0x28 */ RELAYCMD *prelaycmdFirst;
    /* 0x2c */ RELAYCMD *prelaycmdLast;
    /* 0x30 */ RELAYCMD *prelaycmdCur;
    /* 0x34 */ float tCommand;
    /* 0x38 */ int fHandsOff;
    /* 0x3c */ int grfHandsOff;
    /* 0x40 */ RELAYCMD *prelaycmdJt;
    /* 0x44 */ LO *pjt;
    /* 0x48 */ int fHoldBtn10;
    /* 0x4c */ void *pasegaCur;
    /* 0x50 */ RELAY *prelayWait;
    /* 0x54 */ void *pstepAseg;
    /* 0x58 */ void *psmaCur;
    /* 0x5c */ int fSmaReached;
    /* 0x60 */ LO *ploFade;
    /* 0x64 */ LO *ploWidget;
    /* 0x68 */ RELAYCMD *prelaycmdLine;
    /* 0x6c */ void *ptnCur;
    /* 0x70 */ int fHideTn;
    /* 0x74 */ int unk_0x74;
    /* 0x78 */ float sGoTo;
    /* 0x7c */ float sPipe;
    /* 0x80 */ float tBlendEnd;
    /* 0x84 */ int unk_0x84[3];
    /* 0x90 */ int nUnk90;
    /* 0x94 */ int unk_0x94[2];
    /* 0x9c */ int fUnk9c;
    /* 0xa0 */ void *pstepplayerMode;
    /* 0xa4 */ int cstepHold;
    /* 0xa8 */ void *apstepHold[4];
    /* 0xb8 */ int anHold5[4];
    /* 0xc8 */ int anHold6[4];
    /* 0xd8 */ void *pstepSsgGoal;
    /* 0xdc */ void *pssgGoal;
    /* 0xe0 */ int fRun;
    /* 0xe4 */ DLE dleRelay;            /* entry in RELAY::dlJsg */
    /* 0xec */ void *psnd;              /* CRefPtr<SND> */
} JSG;

RELAYCMD *PcmdNew__FP4SCPTii(RELAY *prelay, int relayck, int fAsync);   /* next free command (a dummy when full), zeroed */

#endif
