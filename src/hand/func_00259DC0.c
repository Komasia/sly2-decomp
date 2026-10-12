typedef int qword __attribute__((mode(TI)));
float func_00259DC0(qword *p) { float f; qword t; __asm__("pextuw %0, $0, %1" : "=&r"(t) : "r"(*p)); __asm__("mtc1 %1, %0" : "=f"(f) : "r"(t)); return f; }
