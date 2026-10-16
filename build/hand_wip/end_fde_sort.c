// WIP (Claude agent): 2.95.2-style end_fde_sort (no array checks, heapsort m=n). 138/153: target downheap keeps j/j+1 paths duplicated (no movz), loops not rotated, s0/s2 swapped.
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorg
// SLY2_SAVES: sd
typedef unsigned int size_t;
typedef unsigned int uword;
typedef int sword;
typedef int saddr;
typedef struct dwarf_fde { uword length; sword CIE_delta; void *pc_begin; uword pc_range; } fde;
typedef struct fde_vector { fde **array; size_t count; } fde_vector;
typedef struct fde_accumulator { fde_vector linear; fde_vector erratic; } fde_accumulator;
extern void abort (void);
extern void free (void *);
extern void fde_split (fde_vector *, fde_vector *);
extern void fde_merge (fde_vector *, fde_vector *);

static inline saddr
fde_compare (fde *x, fde *y)
{
  return (saddr)x->pc_begin - (saddr)y->pc_begin;
}

static inline void
frame_downheap (fde **a, size_t lo, size_t hi)
{
  size_t i, j;

  for (i = lo, j = 2*i+1;
       j < hi;
       j = 2*i+1)
    {
      if (j+1 < hi && fde_compare (a[j+1], a[j]) > 0)
        ++j;

      if (fde_compare (a[j], a[i]) > 0)
        {
          fde *tmp = a[i]; a[i] = a[j]; a[j] = tmp;
          i = j;
        }
      else
        break;
    }
}

static inline void
frame_heapsort (fde_vector *erratic)
{
  fde ** a = erratic->array;
  size_t n = erratic->count;
  size_t m;

  m = n;
  while (m > 0)
    frame_downheap (a, --m, n);
  while (n > 1)
    {
      fde *tmp = a[0]; a[0] = a[n-1]; a[n-1] = tmp;
      frame_downheap (a, 0, --n);
    }
}

fde **
end_fde_sort (fde_accumulator *accu, size_t count)
{
  if (accu->linear.count != count)
    abort ();
  fde_split (&accu->linear, &accu->erratic);
  if (accu->linear.count + accu->erratic.count != count)
    abort ();
  frame_heapsort (&accu->erratic);
  fde_merge (&accu->linear, &accu->erratic);
  free (accu->erratic.array);
  return accu->linear.array;
}
