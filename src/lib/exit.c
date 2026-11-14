// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* newlib exit (stdlib/exit.c): run the atexit functions newest first, the reentrancy cleanup, then _exit. */
// name: newlib exit.c (body is the library routine)
struct _atexit { struct _atexit *_next; int _ind; void (*_fns[32])(void); };
struct _reent { char pad[0x3C]; void (*__cleanup)(struct _reent *); char pad2[0x148 - 0x40]; struct _atexit *_atexit; };
extern struct _reent *_impure_ptr;
void _exit(int) __attribute__((noreturn));

void exit(int code)
{
    struct _atexit *p;
    int n;
    for (p = _impure_ptr->_atexit; p; p = p->_next)
        for (n = p->_ind; --n >= 0;)
            (*p->_fns[n])();
    if (_impure_ptr->__cleanup)
        (*_impure_ptr->__cleanup)(_impure_ptr);
    _exit(code);
}
