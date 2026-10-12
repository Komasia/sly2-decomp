class CQueueOutputIop {
public:
    int pad[6];
    int m_x18, m_x1c, m_x20, m_x24, m_x28, m_x2c;
    void Reset();
};
void CQueueOutputIop::Reset()
{
    m_x24 = m_x18;
    m_x28 = 0;
    m_x20 = 0;
    m_x1c = 0;
    m_x2c = 0;
}
