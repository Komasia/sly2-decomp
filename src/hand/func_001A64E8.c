/* BindLoParts (0x1A64E8): fills an object's part pointers from a table of {grf, oid, ib}: each entry's part is stored
 * at the object's +ib: 0x10 its sub-record (of 0x100 bytes, +0x54 / count +0x50) whose +0x9C is the oid (searched from
 * the last); 0x20 its SOE (0x200: turned off); 0x40 its other part 0x1F5FF8 (0x200: 0x1F69F8); else the nearest
 * object of that oid in the world (find kind 4 for 0x2, 5 for 0x1, else 1; 0x400 added to the kind; 0x200: removed
 * with its vt slot 9). SafeHouse brx.cpp. */
#include "so.h"
struct LO;
struct SUB {char pad[0x9C];int x9C;char pad2[0x100-0xA0];};
struct ALO {char pad[0x50];int c;struct SUB*a;};
struct E {int grf,id,ib;};  /* a part entry: flags (GRFPART_*), oid, offset in the object */
#define GRFPART_NEAREST2 0x2
#define GRFPART_NEAREST1 0x1
#define GRFPART_SUBREC 0x10
#define GRFPART_SOE 0x20
#define GRFPART_40 0x40
#define GRFPART_OFF 0x200
#define GRFPART_FIND400 0x400
extern char g_sw[];
void*func_001F6030(struct ALO*,int);
void SetSoeOff__FP3ALOP3SOE(struct ALO*, void*);
void*func_001F5FF8(struct ALO*,int);
void func_001F69F8(struct ALO*,int);
struct LO*PloFindSwNearest__FP2LO3OIDii(void*,int,int,struct ALO*);
// name: SafeHouse port (BindLoParts)
void BindLoParts__FP3ALOiPv(struct ALO*palo,
int c,struct E*ae){
int i=0;
 while(i<c){
  struct E*pe=&ae[i];int grf=pe->grf;
  if(grf&GRFPART_SUBREC){
   /* The count and byte offset share the native search registers. */
   register int j __asm__("$7")=palo->c;register int off __asm__("$6")=j*0x100;struct SUB*p;
   i++;
again:
   j--;off-=0x100;
   if(j<0)goto done;
   p=(struct SUB*)(off+(int)palo->a);
   if(p->x9C!=pe->id)goto again;
   *(void**)((char*)palo+pe->ib)=p;
done:;
  }else if(grf&GRFPART_SOE){
   void*p=func_001F6030(palo,pe->id);
   if(p){i++;*(void**)((char*)palo+pe->ib)=p;if(pe->grf&GRFPART_OFF)SetSoeOff__FP3ALOP3SOE(palo,p);}else i++;
  }else if(grf&GRFPART_40){
   void*p=func_001F5FF8(palo,pe->id);
   if(p){i++;*(void**)((char*)palo+pe->ib)=p;if(pe->grf&GRFPART_OFF)func_001F69F8(palo,pe->id);}else i++;
  }else{
   int k;struct LO*p;
   if(grf&GRFPART_NEAREST2)k=4;else k=(grf&GRFPART_NEAREST1)?5:1;
   p=PloFindSwNearest__FP2LO3OIDii(g_sw,(pe->grf&GRFPART_FIND400)?k|0x400:k,pe->id,palo);
   if(!p){i++;continue;}
   if(pe->grf&GRFPART_OFF)((void (*)(struct LO*))p->pvt[9].pfn)((struct LO*)VT_THIS(p, &p->pvt[9]));
   i++;
   *(void**)((char*)palo+pe->ib)=p;
  }
 }
}

#define OFFSET(t,m) ((unsigned int)&(((t *)0x10000)->m)-0x10000)
typedef char layout_lo_vtable[OFFSET(struct LO,pvt)==12?1:-1];
typedef char layout_sub_id[OFFSET(struct SUB,x9C)==0x9C?1:-1];
typedef char layout_alo_count[OFFSET(struct ALO,c)==0x50?1:-1];
typedef char layout_alo_array[OFFSET(struct ALO,a)==0x54?1:-1];
typedef char layout_entry_flags[OFFSET(struct E,grf)==0?1:-1];
typedef char layout_entry_id[OFFSET(struct E,id)==4?1:-1];
typedef char layout_entry_offset[OFFSET(struct E,ib)==8?1:-1];
typedef char layout_sub_size[sizeof(struct SUB)==0x100?1:-1];
typedef char layout_alo_size[sizeof(struct ALO)==0x58?1:-1];
typedef char layout_entry_size[sizeof(struct E)==12?1:-1];
typedef char layout_word_size[sizeof(int)==4?1:-1];
typedef char layout_pointer_size[sizeof(void*)==4?1:-1];
