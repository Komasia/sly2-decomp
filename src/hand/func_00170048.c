extern char D_002DF740[], D_002DF800[], D_002DF880[], D_002DF940[], D_002DF9C0[], D_002DFA80[];
extern int D_002BE598, D_002BE59C;
void func_0016FCA8(int a, void *b, int c, void *d, int e);
void RememberOverlaySourceFrame__Fv(void);
/* func_00170048: build the frame's three framebuffer setup packets (func_0016FCA8: 12 + 8 qwords each; the second and
 * third with the D_002BE598 / D_002BE59C variants), then the overlay source packets. */
void func_00170048(void) {
    func_0016FCA8(0xC, D_002DF740, 8, D_002DF800, 0);
    func_0016FCA8(0xC, D_002DF880, 8, D_002DF940, D_002BE598);
    func_0016FCA8(0xC, D_002DF9C0, 8, D_002DFA80, D_002BE59C);
    RememberOverlaySourceFrame__Fv();
}
