typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(float f); };
VU_FLOAT::VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=r"(q) : "f"(f)); }
