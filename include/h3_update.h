/* Sly 2 update flags: the word at LO +0x40 (so.h LO::grfUnk40). While the object is not in the world's update table
 * the word holds the flags themselves, tagged with the low bit (GRFUPD_Flags); otherwise it is a pointer to the
 * flags of its update table entry. So code reads it as
 *     grf = plo->grfUnk40; if (!(grf & GRFUPD_Flags)) grf = *(int *)grf;
 * Field names: SafeHouse port (Sly2-Release/update.h). */
#ifndef H3_UPDATE_H
#define H3_UPDATE_H

#define GRFUPD_Flags    0x1     /* the word holds the flags (else it points at them) */
#define GRFUPD_Update   0x2     /* has an update: the Update virtual (vt slot 16) is called each frame */
#define GRFUPD_Unk4     0x4     /* set with GRFUPD_Unk8 when a path's rope simulation starts (SafeHouse rope.cpp: its
                                 * update, vt slot 17, then runs in the physics frame's loop); meaning unknown */
#define GRFUPD_Unk8     0x8     /* set by the laser init (InitLaser) and by some hack-mode objects; meaning unknown */
#define GRFUPD_Unk20    0x20    /* cleared when a path's rope simulation starts, set when it stops; meaning unknown */
#define GRFUPD_Rope     (GRFUPD_Unk4 | GRFUPD_Unk8)    /* the flags a path's rope simulation turns on */
#define GRFUPD_Never    0x40    /* never put in the update table */
#define GRFUPD_RealTime 0x100   /* updated on the real clock (also while the game clock is paused) */

#endif
