class OSTRM { public: int a; void Flush(); ~OSTRM(); };
OSTRM::~OSTRM() { Flush(); }
