/* Sly 2 lasers: the records of class 0x55 (LASER, a set of laser beams, each strung between two endpoints).
 * A LASER keeps an array of beams (LASERPAIR, +0x198 count / +0x19C array, at most 0x40), each with two endpoints
 * (LASEREND). An endpoint is either a fixed point (kind 0, stored in the laser's local space) or a point moving along
 * a path (kind 1: a CRV object and the distance along it, advanced each frame through a 1-, 2- or 6-segment
 * motion profile). The laser also lists up to 7 object ids (+0x150/+0x154) and 7 class ids (+0x170/+0x174) whose
 * objects it overlaps (LaserOverlapKind), and a speed multiplier for the moving endpoints (+0x1C0).
 * Layouts and field names: SafeHouse port (Sly2-Release/laser.cpp, offset comments), checked against the matched code
 * (BindEnd 0x1DE5D8, the endpoint query 0x1DEF98, ApplyLaserContacts 0x1DF260, the endpoint update 0x1DF3D0,
 * AddLaserPair 0x1DF908).
 * The base object (SO / LO, the first 0x150 bytes) is left to the files: this header only holds the laser records. */
#ifndef H3_LASER_H
#define H3_LASER_H

#ifndef H3_QWORD_DEFINED
#define H3_QWORD_DEFINED
typedef int qword __attribute__((mode(TI)));
#endif

struct XP;
struct CRV;

#define CBEAM_LASER_MAX 0x40       /* beams per laser (AddLaserPair) */
#define COID_LASER_MAX 7           /* overlap object ids / class ids per laser */

/* LASEREND::kind */
enum LASERENDK {
    LASERENDK_Nil = -1,            /* not bound yet */
    LASERENDK_Point = 0,           /* fixed point (laser-local space) */
    LASERENDK_Path = 1             /* moving along a path */
};

/* LASERPARAMS::mode: how a path endpoint moves */
enum LASERMODE {
    LASERMODE_Stop = 0,            /* one pass, then a zero-length stationary segment at the far end (2 segments) */
    LASERMODE_Wrap = 8,            /* end to end, wrapping back to the start (1 segment; also any unknown mode) */
    LASERMODE_PingPong = 16        /* there and back, easing in and out at both ends (6 segments) */
};

/* the authored motion of a path endpoint (AddLaserPair; replaced by the LASERMOTION when the endpoint is bound) */
typedef struct LASERPARAMS {       /* field: SafeHouse port */
    /* 0x0 */ float fraction;      /* start position as a fraction of the path length */
    /* 0x4 */ float speed;         /* < 0: runs backwards */
    /* 0x8 */ float duration;      /* time for one pass (overrides speed when > 0) */
    /* 0xc */ int mode;            /* enum LASERMODE */
} LASERPARAMS;

/* one segment of a motion profile: distance = start + speed t + accel t^2 / 2 for t in [0, duration] */
typedef struct LASERSEG {          /* field: SafeHouse port (TRACKSEG) */
    /* 0x00 */ float start;
    /* 0x04 */ float speed;
    /* 0x08 */ float accel;
    /* 0x0c */ float duration;
    /* 0x10 */ float elapsed;      /* time already spent in the segment */
} LASERSEG;   /* 0x14 bytes */

typedef struct LASERMOTION {
    /* 0x00 */ int cseg;
    /* 0x04 */ LASERSEG aseg[6];
    /* 0x7c */ int iseg;           /* the current segment */
} LASERMOTION;

/* LASEREND +0x10 for a path endpoint */
typedef struct LASERTRACK {
    /* 0x00 */ struct CRV *pcrv;   /* the path object (class 10, CID_PATH) */
    /* 0x04 */ float s;            /* current distance along the path */
    /* 0x08 */ union { LASERPARAMS params; LASERMOTION motion; };
} LASERTRACK;

typedef struct LASEREND {          /* field: SafeHouse port */
    /* 0x00 */ int oid;            /* the object the endpoint is bound to (-1: the laser itself) */
    /* 0x04 */ int kind;           /* enum LASERENDK */
    /* 0x08 */ int unk_0x8[2];
    /* 0x10 */ union { qword pos; LASERTRACK track; };   /* pos: kind 0, track: kind 1 (0x88 bytes, padded to 0x90) */
} LASEREND;   /* 0xa0 bytes */

typedef struct LASERPAIR {         /* field: SafeHouse port */
    /* 0x000 */ LASEREND aend[2];
    /* 0x140 */ float sLength;     /* endpoint distance when nothing blocks the beam */
    /* 0x144 */ float sVisible;    /* distance to the nearest contact (the drawn length) */
    /* 0x148 */ struct XP *pxpFirst;   /* the beam's contacts (XP list linked through +0xAC) */
    /* 0x14c */ int unk_0x14c;
} LASERPAIR;  /* 0x150 bytes */

/* LASER +0x1A0 / +0x1B0: an end-cap model drawn at each end of every beam, with an optional animation (ASEG) whose
 * scale channel sizes the cap (bound by func_001DEDB0 in PostLoadLaser, used by CollectLaserDraws) */
typedef struct LASERCAP {
    /* 0x0 */ void *palo;          /* the cap model (an SO; 0: none) - field: SafeHouse port (laserrender.cpp) */
    /* 0x4 */ void *paseg;         /* the first ASEG (class 0x6D) under the model */
    /* 0x8 */ void *pasega;        /* its running ASEGA (t at +0x1C, speed at +0x40) */
    /* 0xc */ void *pevalScale;   /* the scale channel's evaluator (CHN +4; vt slot 3 evaluates it) */
} LASERCAP;

#endif
