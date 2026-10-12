typedef int qword __attribute__((mode(TI)));
float func_00259D98(qword *p) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(*p)); return f; }
