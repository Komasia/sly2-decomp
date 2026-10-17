// v2 (Claude agent): v1 + one `ulong frame` local per DISPLAY in the texture section (ld once + truncation, like the target). aligned 130 (v1 137). Left: target keeps the uninitialised TEX value in fp read ONCE and builds each texture step in temporaries (ours rewrites s3), other stays in s7 (ours spills it), FrameBits constants rematerialised (ours CSEs 0x3F0000/0x3F000000 into s0/s2 and spills vifBuffer).
#define FIELD_OFFSET(t,m) ((uint)&(((t*)0)->m))
#include "gifs.h"
#include "vifs.h"
struct DISPLAY{
 ulong frame;char pad8[8];ulong zbuf;char pad18[8];ulong xyoffset;char pad28[8];ulong scissor;
 char pad38[0x70-0x38];ulong test;char pad78[0xF0-0x78];
};
struct TEXBITS{
 ulong TBP0:14,TBW:6,PSM:6,TW:4,TH:4,TCC:1,TFX:2,CBP:14,CPSM:4,CSM:1,CSA:5,CLD:3;
};
union TEX{ulong word;TEXBITS bits;};
extern int D_002DEDB0;
extern DISPLAY D_002DEBE0,D_002DECD0;
extern "C" void*func_002333B4(void*,int,uint);
static inline ulong FrameBits(ulong frame){ulong data=frame&0x1FFUL;data|=frame&0x3F0000UL;data|=frame&0x3F000000UL;return data;}
typedef char DISPLAY_Size[sizeof(DISPLAY)==240?1:-1];
typedef char TEXBITS_Size[sizeof(TEXBITS)==8?1:-1];
typedef char TEX_Size[sizeof(TEX)==8?1:-1];
typedef char DMAS_Size[sizeof(DMAS)==28?1:-1];
typedef char GIFS_Size[sizeof(GIFS)==40?1:-1];
typedef char VIFS_Size[sizeof(VIFS)==36?1:-1];
typedef char QW_Size[sizeof(QW)==16?1:-1];
typedef char DISPLAY_frame_Offset[FIELD_OFFSET(DISPLAY,frame)==0?1:-1];
typedef char DISPLAY_zbuf_Offset[FIELD_OFFSET(DISPLAY,zbuf)==16?1:-1];
typedef char DISPLAY_xyoffset_Offset[FIELD_OFFSET(DISPLAY,xyoffset)==32?1:-1];
typedef char DISPLAY_scissor_Offset[FIELD_OFFSET(DISPLAY,scissor)==48?1:-1];
typedef char DISPLAY_test_Offset[FIELD_OFFSET(DISPLAY,test)==112?1:-1];
typedef char DMAS_m_ab_Offset[FIELD_OFFSET(DMAS,m_ab)==4?1:-1];
typedef char DMAS_m_pb_Offset[FIELD_OFFSET(DMAS,m_pb)==12?1:-1];
extern "C" void func_0016FCA8(int gifCount,QW*gifBuffer,int vifCount,QW*vifBuffer,uint mask){
 DISPLAY*current;DISPLAY*other;
 if(D_002DEDB0&1){current=&D_002DECD0;other=current-1;}
 else{current=&D_002DEBE0;other=current+1;}
 GIFS gifs;
 gifs.AllocStatic(gifCount,gifBuffer);
 ulong writeMask=(ulong)mask<<32;
 gifs.AddPrimPack(0,1,0xEUL);
 gifs.PackAD(0x4C,FrameBits(current->frame)|writeMask);
 gifs.PackAD(0x4E,current->zbuf);
 gifs.PackAD(0x18,current->xyoffset);
 gifs.PackAD(0x40,current->scissor);
 gifs.PackAD(0x47,current->test);
 gifs.AddPrimPack(0x200,1,0xEUL);
 gifs.PackAD(0x4D,FrameBits(current->frame)|writeMask);
 gifs.PackAD(0x4F,current->zbuf);
 gifs.PackAD(0x19,current->xyoffset);
 gifs.PackAD(0x41,current->scissor);
 gifs.PackAD(0x48,current->test);
 gifs.AddPrimEnd();
 int values[8];func_002333B4(values,0,sizeof(values));
 TEX texture;
 ulong frame=current->frame;
 texture.bits.TBP0=(frame&0x1FFUL)<<5;
 texture.bits.TBW=(frame>>16)&0x3FUL;
 texture.bits.PSM=0;
 texture.bits.TW=10;
 texture.bits.TH=10;
 texture.bits.TCC=1;
 texture.bits.TFX=0;
 values[0]=(int)frame;
 values[2]=(int)texture.word;
 values[4]=(int)((frame&~0x3F000000UL)|0x02000000UL);
 texture.bits.PSM=2;
 values[6]=(int)texture.word;
 frame=other->frame;
 texture.bits.TBP0=(frame&0x1FFUL)<<5;
 texture.bits.TBW=(frame>>16)&0x3FUL;
 texture.bits.PSM=0;
 values[1]=(int)frame;
 values[3]=(int)texture.word;
 values[5]=(int)((frame&~0x3F000000UL)|0x02000000UL);
 texture.bits.PSM=2;
 values[7]=(int)texture.word;
 VIFS vifs;
 vifs.AllocStatic(vifCount,vifBuffer);vifs.AddDmaCnt();
 vifs.AddVifDirectRefs(gifCount,gifBuffer,0);
 vifs.AddVifBaseOffset(0,0);
 vifs.AddVifUnpack(UPK_V4_32,2,values,0xB);
 vifs.EndDmaCnt();vifs.AddDmaRet();
}
