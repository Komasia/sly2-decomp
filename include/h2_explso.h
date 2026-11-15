/* EXPLSO: the parameter block of an explosion's burst (Sly 1 emitter.h EXPLSO; the Sly 2 layout from the matched
 * code and SafeHouse's BURSTPARAMS, emitter.h). The grfexplso bits say which of the fields override the
 * explosion's own settings. Passed to an explosion's vtable slot 51 (ExplodeXxxExplso) / slot 52 (FireXxxExplso). */
#ifndef H2_EXPLSO_H
#define H2_EXPLSO_H

#ifndef SLY2_QWORD
#define SLY2_QWORD
typedef int qword __attribute__((mode(TI)));
#endif

/* grfexplso bits (field: SafeHouse port, BURSTPARAMS) */
#define GRFEXPLSO_Reference 0x01   /* paloReference: the source object */
#define GRFEXPLSO_Vec       0x02   /* vec: the burst direction */
#define GRFEXPLSO_Pos       0x04   /* posOrigin: the burst position (a point) */
#define GRFEXPLSO_Scale     0x08   /* rScale: the density (0: sRadius / 100) */
#define GRFEXPLSO_Radius    0x10   /* the particles' size (rScale) */
#define GRFEXPLSO_Touch     0x20   /* psoTouch: the object the particles touch */
#define GRFEXPLSO_Olxf      0x40   /* pemitolxf: a frame to burst in */
#define GRFEXPLSO_Count     0x80   /* cParticle: the particle count */

typedef struct EXPLSO {
    /* 0x00 */ int grfexplso;
    /* 0x04 */ void *paloReference;
    /* 0x08 */ float rScale;
    /* 0x0c */ float sRadius;
    /* 0x10 */ qword vec;
    /* 0x20 */ qword posOrigin;
    /* 0x30 */ void *psoTouch;
    /* 0x34 */ struct EMITOLXF *pemitolxf;
    /* 0x38 */ int cParticle;
    /* 0x3c */ int unk_0x3c;
} EXPLSO;   /* 0x40 bytes */

#endif
