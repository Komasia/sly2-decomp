typedef struct { unsigned char c[4]; } RGBA;
typedef struct { int pad[4]; RGBA c; } P;
void func_00258458(P *p, RGBA *c) { p->c = *c; }
