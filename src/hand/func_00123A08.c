typedef struct CRef { int m_tagk; float m_g; } CRef;
extern float g_clock;
CRef *RefOpCurrentTime__FiP4CRefP6CFrame(CRef *ret)
{
    ret->m_tagk = 0x16;
    ret->m_g = g_clock;
    return ret;
}
