/* class: a splice method's body (the wrapper 0x105CD0 passes the object and its one object argument): the argument,
 * if any, is told the guard commands (TellGuardCommands) with the object. */
typedef struct LO LO;
void TellGuardCommands__FP2LOi(LO *plo, int n);

void func_00170E68(void *pbasic, LO *plo)
{
    if (plo != 0) {
        TellGuardCommands__FP2LOi(plo, (int)pbasic);
    }
}
