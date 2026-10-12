extern "C" void func_00170348(void);
class CProg {
public:
    int m_fActive; int m_nMax; int m_nTarget; int m_nRemain; char m_f10; char pad[0x3f]; int m_cRetry;
    void SetRemain(int nRemain);
    void Draw();
};
void CProg::SetRemain(int nRemain)
{
    if (m_fActive != 0) {
        if (m_nTarget == 0) {
            m_nTarget = nRemain;
            m_nMax = nRemain << 1;
            func_00170348();
        } else if (m_nRemain == nRemain) {
            m_cRetry = m_cRetry + 1;
        } else {
            m_cRetry = 0;
        }
        m_nRemain = nRemain;
        Draw();
    }
}
