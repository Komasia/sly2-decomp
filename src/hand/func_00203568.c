struct S { char pad[0xF4]; int a; int b; int c; char pad2[0x10]; int d; };
void InitXfm__FP3XFM(struct S *p);
void InitPhotoTarget__FP2LO(struct S *p) { InitXfm__FP3XFM(p);
p->a = -1; //P
p->d = -1; //P
p->c = -1; //P
p->b = -2; //P
}

// name: SafeHouse port (InitPhotoTarget)