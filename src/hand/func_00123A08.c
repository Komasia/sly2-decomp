/* BIF current-time: the game clock's time. */
#include "splice.h"
/* layout note: g_clock (0x2DDF0C) is declared as a bare float here - with clock.h's CLOCK the load is scheduled
 * differently. The value read is g_clock.t. */
extern float g_clock;
CRef *RefOpCurrentTime__FiP4CRefP6CFrame(CRef *ret)
{
    ret->m_tagk = TAGK_F32;
    ret->m_tag.m_g = g_clock;
    return ret;
}
