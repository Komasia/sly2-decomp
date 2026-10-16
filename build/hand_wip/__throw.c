// WIP (Claude agent): 80/119 diffs; frame/slots right (Sony 2.95.2 source: two frame_states, memcpy, throw_helper(..,&udata), eh_return(udata->cfa - my_udata->cfa)). Left: target copies __frame_state_for result v0->v1 before test, memcpy loop reg order a1..t0; pu if/else emulates Sony PRE edge insertion.
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorg
// SLY2_SAVES: sd
#define FIRST_PSEUDO_REGISTER 79
typedef struct frame_state
{
  void *cfa;
  void *eh_ptr;
  long cfa_offset;
  long args_size;
  long reg_or_offset[FIRST_PSEUDO_REGISTER+1];
  unsigned short cfa_reg;
  unsigned short retaddr_column;
  char saved[FIRST_PSEUDO_REGISTER+1];
} frame_state;
struct eh_context
{
  void *handler_label;
  void **dynamic_handler_chain;
  void *info;
  void *table_index;
};
extern struct eh_context *(*get_eh_context) (void);
extern void __terminate (void);
extern struct frame_state *__frame_state_for (void *, struct frame_state *);
extern void *throw_helper (struct eh_context *eh, void *pc, frame_state *my_udata, frame_state **udata_p);

void
__throw ()
{
  struct eh_context *eh = (*get_eh_context) ();
  void *pc, *handler;

  /* XXX maybe make my_ustruct static so we don't have to look it up for
     each throw.  */
  frame_state ustruct;
  frame_state *udata = &ustruct;
  frame_state my_ustruct, *my_udata = &my_ustruct;
  frame_state **pu;

  if (! eh->info)
    {
      __terminate ();
      pu = &udata;
    }
  else
    pu = &udata;
label:
  udata = __frame_state_for (&&label, udata);
  if (! udata)
    __terminate ();

  udata->cfa = __builtin_dwarf_cfa ();

  __builtin_memcpy (my_udata, udata, sizeof (*udata));

  __builtin_unwind_init ();

  pc = __builtin_extract_return_addr (__builtin_return_address (0)) - 1;

  handler = throw_helper (eh, pc, my_udata, pu);

  __builtin_eh_return ((void *)eh, udata->cfa - my_udata->cfa, handler);
}
