/* __errno (0x2401C8; newlib errno.c): the address of errno, the first field of the current reentrancy struct
 * (_impure_ptr); the libm functions (log10, pow, ...) set errno through it. */
// name: newlib (__errno: int *__errno(void) { return &_REENT->_errno; })
extern int *_impure_ptr;   /* struct _reent: _errno first */

int *__errno(void)
{
    return _impure_ptr;
}
