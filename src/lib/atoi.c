// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* atoi (newlib): strtol(s, 0, 10) as an int. */
long strtol(const char *, char **, int);
int atoi(const char *s) { return (int)strtol(s, 0, 10); }
