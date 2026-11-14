// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
void _exit(int) __attribute__((noreturn));
/* abort: the SDK libc stub, _exit(1) (libgcc frame code calls it on corrupt unwind data). */
void abort(void) { _exit(1); }
