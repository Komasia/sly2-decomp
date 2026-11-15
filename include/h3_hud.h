/* Sly 2 in-game HUD widgets (module 0x1D93D8..0x1DFAD8): constants shared by the gauge (D_003D9E80, the health and
 * gadget power meter), the prompt (D_003DA0C0) and the other widgets.
 * Names: SafeHouse port (Sly2-Release/hudwidget.cpp), checked against the matched code (InitGauge 0x1D9968,
 * SetGaugeState 0x1D9B60, UpdateGauge 0x1D9DF8, SetPromptState 0x1DA5C8, UpdatePrompt 0x1DA350). */
#ifndef H3_HUD_H
#define H3_HUD_H

/* screen objects found by the widgets (PloFindSwNearest(&g_sw, 0x405, oid, 0)) */
#define OID_SCREENGAUGE 0x36B
#define OID_SCREENPROMPT 0x371

/* parts of the gauge's screen object */
#define WID_HEALTHMETER 0x34F           /* the health meter (fraction 1 - health) */
#define WID_POWERMETER 0x350            /* the gadget power meter */

/* parts of the prompt's screen object */
#define WID_PROMPTIN 0x310              /* played when a changed prompt comes back in */
#define WID_PROMPTCHANGE 0x312          /* played while the prompt changes to the next one */

/* the gauge's screen object animations: 5 per player class (idle, hit, hide, back, low), from these bases */
#define IDGAUGE_Player 0x33D            /* class 0x35 and the default */
#define IDGAUGE_Player36 0x342          /* class 0x36 */
#define IDGAUGE_Player37 0x347          /* class 0x37 */

/* gauge states (GAUGE +0x30) */
enum GAUGES {
    GAUGES_Hidden = 0,                  /* no player, or the player is down */
    GAUGES_Idle = 1,
    GAUGES_Hit = 2,                     /* health went down: the hit animation, then GAUGES_Heal */
    GAUGES_Heal = 3,                    /* the health meter smoothed to the player's health */
    GAUGES_Power = 4,                   /* the power meter smoothed to the player's power */
    GAUGES_Back = 5,                    /* the player changed: the hide animation, then idle */
    GAUGES_State6 = 6,                  /* player +0x10C8 != -1 (animation 3) */
    GAUGES_State7 = 7                   /* player +0x10EC == 4 (animation 4) */
};

/* prompt states (PROMPT +0x10) */
enum PROMPTS {
    PROMPTS_Nil = -1,
    PROMPTS_Off = 0,
    PROMPTS_Opening = 1,                /* shown, until its screen object reaches state 2 */
    PROMPTS_Shown = 2,
    PROMPTS_Closing = 3,                /* hidden, until its screen object is below state 2 */
    PROMPTS_Changing = 4                /* WID_PROMPTCHANGE playing, then the next prompt */
};

#endif
