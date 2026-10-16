// WIP (Claude agent): SPLIT ISSUE - functions.csv range 0x23E4A0-0x23E730 also contains __sjpopnthrow (starts 0x23E618, frameless-fp copy of the cleanup loop then jal __sjthrow). __sjthrow part: frame/slots right with -fstrict-aliasing; left = target keeps cleanup[0] in v1 across loop / load order of *dhc=buf.
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY2_ASM: gnu-reorg
// SLY2_SAVES: sd
struct eh_context
{
  void *handler_label;
  void **dynamic_handler_chain;
  void *info;
  void *table_index;
};
extern struct eh_context *(*get_eh_context) (void);
extern void __terminate (void);

void
__sjthrow ()
{
  struct eh_context *eh = (*get_eh_context) ();
  void ***dhc = &eh->dynamic_handler_chain;
  void *jmpbuf;
  void (*func)(void *, int);
  void *arg;
  void ***cleanup = (void***)&(*dhc)[1];

  if (cleanup[0])
    {
      double store[200];
      void **buf = (void**)store;
      buf[1] = 0;
      buf[0] = (*dhc);

      if (! __builtin_setjmp (&buf[2]))
	{
	  *dhc = buf;
	  while (cleanup[0])
	    {
	      func = (void(*)(void*, int))cleanup[0][1];
	      arg = (void*)cleanup[0][2];

	      cleanup[0] = (void **)cleanup[0][0];

	      (*func)(arg, 2);
	    }
	  *dhc = buf[0];
	}
      else
	{
	  __terminate ();
	}
    }
  
  if (! eh->info || (*dhc)[0] == 0)
    __terminate ();
    
  jmpbuf = &(*dhc)[2];

  *dhc = (void**)(*dhc)[0];

  __builtin_longjmp (jmpbuf, 1);
}
