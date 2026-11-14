/* strtol (0x234580; newlib strtol.c): _strtol_r (0x234350) on the current thread's reentrancy struct
 * (_impure_ptr); atoi calls it. */
// name: newlib (strtol: long strtol(const char *s, char **ptr, int base) { return _strtol_r(_REENT, s, ptr, base); })
struct _reent;
extern struct _reent *_impure_ptr;
long _strtol_r(struct _reent *rptr, const char *s, char **ptr, int base);

long strtol(const char *s, char **ptr, int base)
{
    return _strtol_r(_impure_ptr, s, ptr, base);
}
