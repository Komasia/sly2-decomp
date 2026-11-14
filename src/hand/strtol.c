/* strtol (0x234580; newlib strtol.c): _strtol_r (0x234350) on the current thread's reentrancy struct
 * (_impure_ptr); atoi calls it. */
// name: newlib (strtol: long strtol(const char *s, char **ptr, int base) { return _strtol_r(_REENT, s, ptr, base); })
struct _reent;
extern struct _reent *D_002C49D4;   /* _impure_ptr */
long func_00234350(struct _reent *rptr, const char *s, char **ptr, int base);   /* _strtol_r */

long strtol(const char *s, char **ptr, int base)
{
    return func_00234350(D_002C49D4, s, ptr, base);
}
