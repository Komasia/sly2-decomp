/* Sly 2 vehicles: the record types of class 0x4D (VEHICLE, the wheeled vehicles), class 0x99 (VEHICLEATTACH, a
 * vehicle's weapon/attachment) and class 0x6C (vehicle pickups).
 * Layouts and field names: SafeHouse port (Sly2-Release/vehicle.h, vehiclebindings.cpp offset comments), checked
 * against the matched code (AddVehicleWheel 0x1D4B48, AddVehicleSide 0x1D4C48, the attachment constructor 0x1D4B90 /
 * InitVehicleAttach 0x1D4D30, the resource accessors 0x1D4CE0..0x1D4D18).
 * The base object (ALO / SO / LO, the first 0x150 / 0x180 bytes) is left to the files: this header only holds the
 * vehicle-specific records. */
#ifndef H3_VEHICLE_H
#define H3_VEHICLE_H
#include "util.h"

#ifndef H3_QWORD_DEFINED
#define H3_QWORD_DEFINED
typedef int qword __attribute__((mode(TI)));
#endif

struct XF;
struct XP;
struct LO;

/* one wheel (VEHICLE +0x1A0, up to 8, count at +0x190) */
typedef struct VEHICLEWHEEL {      /* field: SafeHouse port */
    /* 0x00 */ int id;             /* oid of the wheel's transform node */
    /* 0x04 */ struct XF *pxf;     /* the wheel's transform node */
    /* 0x08 */ struct XP *pxp;     /* this wheel's contact list */
    /* 0x0c */ float steerFraction;
    /* 0x10 */ float sideFraction;
    /* 0x14 */ float tilt;
    /* 0x18 */ float speed;        /* rolling speed (rad/s) */
    /* 0x1c */ float angle;        /* rolling angle */
    /* 0x20 */ float radius;
    /* 0x24 */ LM lmTravel;        /* suspension travel: bottom, top */
    /* 0x2c */ int unk_0x2c;
    /* 0x30 */ qword position;
    /* 0x40 */ qword upper;
    /* 0x50 */ qword lower;
} VEHICLEWHEEL;                    /* 0x60 */

/* one steering side (VEHICLE +0x4A8, up to 4, count at +0x4A4) */
typedef struct VEHICLESIDE {       /* field: SafeHouse port */
    /* 0x00 */ int id;
    /* 0x04 */ struct XF *pxf;
    /* 0x08 */ void *pctrlpos;     /* CTRLPOS controller */
    /* 0x0c */ LM lmLimits;
} VEHICLESIDE;                     /* 0x14 */

/* one ammunition resource (VEHICLE +0x574, 3 of them) */
typedef struct VEHICLERESOURCE {   /* field: SafeHouse port */
    /* 0x0 */ int count;
    /* 0x4 */ int maximum;
    /* 0x8 */ float priority;
} VEHICLERESOURCE;                 /* 0xC */

#define CVEHICLEWHEEL_MAX 8
#define CVEHICLESIDE_MAX 4
#define CVEHICLEATTACH_MAX 8

/* vehicle modes (VEHICLE +0x180, SetVehicleMode) */
enum VEHICLEMODE {
    VEHICLEMODE_Nil = -1,
    VEHICLEMODE_Idle = 0,          /* parked: no health widget, engine sound stopped (post-load mode) */
    VEHICLEMODE_Ai = 1,            /* driven by its AI (SetVehicleAiState) */
    VEHICLEMODE_Focus = 2,         /* driven by the player (SafeHouse SetVehicleFocus) */
    VEHICLEMODE_Dead = 3           /* destroyed (health reached 0, AcceptVehicleContact) */
};

/* vehicle pickup states (pickup +0x150, SetVehiclePickupState) */
enum VEHICLEPICKUPSTATE {
    VEHICLEPICKUPSTATE_Nil = -1,
    VEHICLEPICKUPSTATE_Landing = 0,   /* placed, waiting for its position record to come to rest (mode 3) */
    VEHICLEPICKUPSTATE_Ready = 1,     /* at rest, can be collected */
    VEHICLEPICKUPSTATE_Collected = 2
};

#endif
