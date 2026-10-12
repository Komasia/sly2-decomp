class CProg { public: int m_cRetry; int m_nRemain; int m_nTarget; int m_nMax; char m_fActive; char pad[0x3f]; int m_n50; void Begin(); };
void CProg::Begin() { m_cRetry = 0; m_n50 = 0; m_nMax = 0; m_nTarget = 0; m_nRemain = 0; m_fActive = 0; }
