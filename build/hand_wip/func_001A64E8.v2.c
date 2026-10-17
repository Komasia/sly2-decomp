// wip (Claude agent, nonvu14, 2026-10-17): aligned 8 (v1 26). Dropped the $19/$18 register pins on palo/i (param used directly). Left: first loop j/p get a1/a3 (target a3/a1) and addu operand order.
struct LO;
typedef struct {short d,pad;void(*pfn)(struct LO*);} VTE;
struct LO {int x0,x4,x8;VTE*vt;};
struct SUB {char pad[0x9C];int x9C;char pad2[0x100-0xA0];};
struct ALO {char pad[0x50];int c;struct SUB*a;};
struct E {int grf,id,ib;};
extern char D_003DD490[];
void*func_001F6030(struct ALO*,int);
void func_001F2AD0(struct ALO*, void*);
void*func_001F5FF8(struct ALO*,int);
void func_001F69F8(struct ALO*,int);
struct LO*func_0015E938(void*,int,int,struct ALO*);
void func_001A64E8(struct ALO*palo,
int c,struct E*ae){
int i=0;
 while(i<c){
  struct E*pe=&ae[i];int grf=pe->grf;
  if(grf&0x10){
   int j=palo->c;int off=j*0x100;struct SUB*p;
   i++;
again:
   j--;off-=0x100;
   if(j<0)goto done;
   p=(struct SUB*)((char*)palo->a+off);
   if(p->x9C!=pe->id)goto again;
   *(void**)((char*)palo+pe->ib)=p;
done:;
  }else if(grf&0x20){
   void*p=func_001F6030(palo,pe->id);
   if(p){i++;*(void**)((char*)palo+pe->ib)=p;if(pe->grf&0x200)func_001F2AD0(palo,p);}else i++;
  }else if(grf&0x40){
   void*p=func_001F5FF8(palo,pe->id);
   if(p){i++;*(void**)((char*)palo+pe->ib)=p;if(pe->grf&0x200)func_001F69F8(palo,pe->id);}else i++;
  }else{
   int k;struct LO*p;
   if(grf&2)k=4;else k=(grf&1)?5:1;
   p=func_0015E938(D_003DD490,(pe->grf&0x400)?k|0x400:k,pe->id,palo);
   if(!p){i++;continue;}
   if(pe->grf&0x200)p->vt[9].pfn((struct LO*)((char*)p+p->vt[9].d));
   i++;
   *(void**)((char*)palo+pe->ib)=p;
  }
 }
}
