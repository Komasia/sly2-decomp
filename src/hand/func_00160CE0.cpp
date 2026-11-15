// name: Sly 1 frm.c ClearPendingFrame (suggested by h2)
// ClearPendingFrame__FP3FRM (Sly 1 frm.c ClearPendingFrame): empty a frame's pending-release lists once it is rendered: each
// object is unlinked and released (vtable entry 2), each buffer freed (its storage too) back to its slot heap.
#include "so.h"
extern void*s_pdliFirst;
struct DLI{
 DL*list;void**next;int linkOffset;void*previous;
 DLI(DL*owner){int offset=owner->ibDle;previous=s_pdliFirst;s_pdliFirst=this;list=owner;next=(void**)owner;linkOffset=offset;}
 ~DLI(){s_pdliFirst=previous;}
 void*Next(){void*value=*next;next=(void**)((unsigned int)value+linkOffset);return value;}
};
struct BUF{char pad[0x1088];void*storage;};
struct FRM{char pad[0x34];DL dlRelease,dlFree;};
extern char D_003E1530[],D_003E1518[];   /* the slot heaps of the storage / the buffers */
extern "C" int FIsDlEmpty(DL*) asm("FIsDlEmpty__FP2DL");
extern "C" void RemoveDlEntry(DL*,void*) asm("RemoveDlEntry__FP2DLPv");
extern "C" void ClearDl(DL*) asm("ClearDl__FP2DL");
extern "C" void func_0011CD98(void*,void*);   /* free a slot */
extern "C" void ClearPendingFrame__FP3FRM(FRM*frame){
 if(!FIsDlEmpty(&frame->dlRelease)){
  DLI iter(&frame->dlRelease);
  for(LO*object=(LO*)iter.Next();object;object=(LO*)iter.Next()){
   RemoveDlEntry(&frame->dlRelease,object);
   VTENT*entry=&object->pvt[2];((void (*)(void*))entry->pfn)(VT_THIS(object, entry));
  }
  ClearDl(&frame->dlRelease);
 }
 if(!FIsDlEmpty(&frame->dlFree)){
  DLI iter(&frame->dlFree);
  for(BUF*object=(BUF*)iter.Next();object;object=(BUF*)iter.Next()){
   if(object->storage)func_0011CD98(D_003E1530,object->storage);
   RemoveDlEntry(&frame->dlFree,object);
   func_0011CD98(D_003E1518,object);
  }
  ClearDl(&frame->dlFree);
 }
}

#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef char Pointer_Size[sizeof(void*)==4?1:-1];
typedef char Integer_Size[sizeof(int)==4&&sizeof(unsigned int)==4?1:-1];
typedef char DLI_Size[sizeof(DLI)==16?1:-1];
typedef char DLI_List[FIELD_OFFSET(DLI,list)==0?1:-1];
typedef char DLI_Next[FIELD_OFFSET(DLI,next)==4?1:-1];
typedef char DLI_LinkOffset[FIELD_OFFSET(DLI,linkOffset)==8?1:-1];
typedef char DLI_Previous[FIELD_OFFSET(DLI,previous)==12?1:-1];
typedef char BUF_PrefixSize[sizeof(BUF)==0x108C?1:-1];
typedef char BUF_Storage[FIELD_OFFSET(BUF,storage)==0x1088?1:-1];
typedef char FRM_PrefixSize[sizeof(FRM)==0x4C?1:-1];
typedef char FRM_FirstList[FIELD_OFFSET(FRM,dlRelease)==0x34?1:-1];
typedef char FRM_SecondList[FIELD_OFFSET(FRM,dlFree)==0x40?1:-1];
