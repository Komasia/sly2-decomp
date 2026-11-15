/* DAMAGE: an actor's damage controller (ACTOR +0xDF0; module 0x1A0B18..0x1A2CC0: InitDamage, SetDamageState,
 * FAcceptDamage, UpdateDamage, the Next* reaction ends). Its state +0x4 is ACTOR +0xDF4: -1 none, 0..12 the reactions
 * (7 knocked back, 8 / 9 a deadly launch, 3 / 10 water, 1 / 2 stunned, 4 / 12, 5 / 11). A hit is a contact message
 * (SafeHouse so.h CTMSG) copied to +0x30.
 * Layout: SafeHouse port (actor.h DAMAGE, so.h CTMSG); only the fields the C sources use. */
#ifndef H5_DAMAGE_H
#define H5_DAMAGE_H

struct ACTOR;
struct LO;
struct ASEG;
struct ASEGA;

/* the hit kinds (CTMSG grfFilter), by what FAcceptDamage / ApplyDamageVelocity do with them */
#define GRFDMG_MURRAY      0x40       /* hit by Murray: knocked to his left or right */
#define GRFDMG_PUSH        0x100      /* pushed away from the sender and up */
#define GRFDMG_LAUNCH      0x200      /* launched along the message's velocity */
#define GRFDMG_REACT4      0x400      /* reaction 4 (12 when out of health) */
#define GRFDMG_STUN1       0x800      /* stunned: reaction 1, then NextStunned */
#define GRFDMG_STUN2       0x1000     /* stunned: reaction 2, then NextStunned */
#define GRFDMG_WATER       0x2000     /* in the water: reaction 3 (10 when out of health) */
#define GRFDMG_REACT5      0x4000     /* reaction 5 (11 when out of health), facing the camera */
#define GRFDMG_BURN        0x8000     /* launched, then the burn's end (NextSpecial) */
#define GRFDMG_HEAL        0x100000   /* healing (SafeHouse) */

/* the reaction's deferred end: a pointer to member function of DAMAGE (g++ 2.x layout) */
struct DAMAGEPMF {
    short delta;
    unsigned short idx;        /* 0: none */
    void (*pfn)(void *);
};

/* the hit (a copy of the CTMSG accepted) */
struct DAMAGEMSG {
    /* 0x00 */ struct LO *ploSender;
    /* 0x04 */ int pad4, pad8;
    /* 0x0c */ int grfFilter;     /* the hit's kind (GRFDMG_*) */
    /* 0x10 */ int dn;            /* nState: the counter's change */
    /* 0x14 */ char pad14[0x30 - 0x14];
    /* 0x30 */ int vec[3];        /* the velocity */
    /* 0x3c */ char pad3C[0x60 - 0x3C];
} __attribute__((aligned(16)));

struct DAMAGE {
    /* 0x00 */ struct ACTOR *pactor;
    /* 0x04 */ int nState;              /* the reaction (ACTOR +0xDF4) */
    /* 0x08 */ float tStart;            /* field: SafeHouse port - the reaction's start */
    /* 0x0c */ int cCapacity;           /* field: SafeHouse port */
    /* 0x10 */ int *pcount;             /* field: SafeHouse port - the counter (Sly: the save's health) */
    /* 0x14 */ char pad14[0x1C - 0x14];
    /* 0x1c */ struct DAMAGEPMF pmfNext; /* field: SafeHouse port (pfnNext) - the action at the reaction's end */
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ struct DAMAGEMSG msg;    /* field: SafeHouse port (req) - the last hit */
    /* 0x90 */ int nFlash;              /* field: SafeHouse port - the flashing (-1 none, 1 hit, 0 healing) */
    /* 0x94 */ float tFlash;            /* field: SafeHouse port - its start */
    /* 0x98 */ float tFlashFade;        /* field: SafeHouse port - its fade's start (FLT_MAX while reacting) */
    /* 0x9c */ float dtFlash;           /* field: SafeHouse port - its length */
    /* 0xa0 */ struct ASEG *apasegReaction[13];  /* the reactions' segments by state */
    /* 0xd4 */ char padD4[0x108 - 0xD4];
    /* 0x108 */ struct ASEG *pasegHeal;  /* the healing clip */
    /* 0x10c */ struct ASEGA *pasegaHeal; /* field: SafeHouse port - its ASEGA */
};

#define H5_DAMAGE_OFFSET(t, m) ((unsigned int)&(((t *)0)->m))
typedef char H5_DAMAGE_pcount[H5_DAMAGE_OFFSET(struct DAMAGE, pcount) == 0x10 ? 1 : -1];
typedef char H5_DAMAGE_pmfNext[H5_DAMAGE_OFFSET(struct DAMAGE, pmfNext) == 0x1C ? 1 : -1];
typedef char H5_DAMAGE_msg[H5_DAMAGE_OFFSET(struct DAMAGE, msg) == 0x30 ? 1 : -1];
typedef char H5_DAMAGE_grfFilter[H5_DAMAGE_OFFSET(struct DAMAGE, msg.grfFilter) == 0x3C ? 1 : -1];
typedef char H5_DAMAGE_nFlash[H5_DAMAGE_OFFSET(struct DAMAGE, nFlash) == 0x90 ? 1 : -1];
typedef char H5_DAMAGE_apasegReaction[H5_DAMAGE_OFFSET(struct DAMAGE, apasegReaction) == 0xA0 ? 1 : -1];
typedef char H5_DAMAGE_pasegaHeal[H5_DAMAGE_OFFSET(struct DAMAGE, pasegaHeal) == 0x10C ? 1 : -1];
typedef char H5_DAMAGE_size[sizeof(struct DAMAGE) == 0x110 ? 1 : -1];

#endif
