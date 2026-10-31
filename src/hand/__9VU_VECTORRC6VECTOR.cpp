/* VU_VECTOR::VU_VECTOR(const VECTOR &) (Sly 1 vec.h): load a VECTOR into a VU register-sized quadword. */
typedef int qword __attribute__((mode(TI)));

struct VECTOR {
    qword qw;
};

struct VU_VECTOR {
    qword m_vu;
    VU_VECTOR(const VECTOR &vec);
};

VU_VECTOR::VU_VECTOR(const VECTOR &vec)
{
    m_vu = vec.qw;
}
