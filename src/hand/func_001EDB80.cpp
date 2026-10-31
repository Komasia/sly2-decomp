/* PsaiFromSaaShd (Sly 1 shdanim.c): does this animation drive shader pshd? Sly 2 returns the test itself (Sly 1
 * returned &psaa->sai or NULL). */
#include "shdanim.h"

int PsaiFromSaaShd(SAA *psaa, SHD *pshd)
{
    return pshd->oid == psaa->oid;
}
