/* SetBentleyJumpState: the jump code's state kinds mapped to Bentley's states (0 stand, 2 jump, 3 interact, 4
 * damage, 9-12 the animation / throw states, 13 climb); the inverse of BentleyJumpKind. */
void SetBentleyState__FP7BENTLEYi(void *, int);
// name: SafeHouse port (SetBentleyJumpState)
void SetBentleyJumpState__FP2LOi(void *pbentley, unsigned int jumpk) {
    switch (jumpk) {
    case 0: SetBentleyState__FP7BENTLEYi(pbentley, 0); break;
    case 1: SetBentleyState__FP7BENTLEYi(pbentley, 2); break;
    case 2: SetBentleyState__FP7BENTLEYi(pbentley, 3); break;
    case 3: SetBentleyState__FP7BENTLEYi(pbentley, 4); break;
    case 4: SetBentleyState__FP7BENTLEYi(pbentley, 9); break;
    case 5: SetBentleyState__FP7BENTLEYi(pbentley, 10); break;
    case 6: SetBentleyState__FP7BENTLEYi(pbentley, 11); break;
    case 7: SetBentleyState__FP7BENTLEYi(pbentley, 12); break;
    case 8: SetBentleyState__FP7BENTLEYi(pbentley, 13); break;
    }
}
