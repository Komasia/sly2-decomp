/* Object finds (CFindObjects 0x15E678, CFindObjectsByClass 0x15E9C8 and their wrappers): the grf argument.
 * The low byte is the find kind (SafeHouse spliceglue.cpp: 1 below the context, 2 the context's children, 3 the
 * context's ancestors, 4 the nearest shared namespace, 5 anywhere); the higher bits modify it. */
#ifndef H2_FIND_H
#define H2_FIND_H

#define FINDK_Mask        0xFF
#define FINDK_Below       1
#define FINDK_Children    2
#define FINDK_Ancestors   3
#define FINDK_Nearest     4
#define FINDK_Any         5

#define GRFFIND_Active    0x100   /* only objects with their active bit set */
#define GRFFIND_CountAll  0x200   /* return the full count, not clamped to cMax */
#define GRFFIND_AnyNs     0x400   /* skip the namespace check */
#define GRFFIND_NsFirst   0x800   /* only the nearest namespace */

#endif
