// Initialize the fixed GIF register packets.
#include "qw.h"
struct BUILDER {uchar *maximum,*base;QW *count;uchar *cursor;int pad,endPrim;void *vt;QW *primitive;uint registers,allRegisters;};
extern "C" {BUILDER *func_00166920(BUILDER *);void func_00157330(BUILDER *,int,QW *);void func_00166B10(BUILDER *,int,int,int,ulong,QW **);void func_00166BD8(BUILDER *,int,int,ulong);void func_00166E90(BUILDER *,long,long);void func_00166968(BUILDER *);}

extern QW D_004421B0[7];
extern QW D_00442240[0x27];
extern QW D_00442210[3];
extern QW D_004424B0[2];
extern QW D_004424D0[2];
extern QW D_00442560[4];
extern QW D_004425A0[3];
extern QW D_004424F0[3];
extern QW D_00442520[4];
extern int D_002EDDB0;
extern ulong D_002EDCE0,D_002EDBF0;
extern "C" void func_00211528(){
 BUILDER setup,tiles,frame,unmask,mask,restore,region,test,enable;
 register int remaining asm("$20")=0x1E0;
 register int first asm("$21")=0x7000;
 register ulong one asm("$18")=1;
 func_00166920(&setup);
 register QW *data asm("$16")=D_004421B0;
 register QW *header asm("$17")=(QW *)((int)data-0x10);
 func_00157330(&setup,7,data);
 ((QW *)((int)data-0x10))->aul[0]=1UL<<60;header->aul[1]=5;
 func_00166B10(&setup,0x44,0,1,1,0);header[1].aul[0]|=one;
 func_00166B10(&setup,0x84,0,1,1,0);header[2].aul[0]|=one;
 func_00166B10(&setup,0x45,0,1,1,0);header[3].aul[0]|=one;
 func_00166B10(&setup,0x85,0,1,1,0);header[4].aul[0]|=one;
 func_00166B10(&setup,0x42,0,1,1,0);header[5].aul[0]|=one;
 int second=0x7200;
 func_00166B10(&setup,0x82,0,1,1,0);header[6].aul[0]|=one;
 register BUILDER *tile asm("$16")=&tiles;
 BUILDER *coordinates=tile;
 func_00166920(tile);
 func_00157330(tile,0x27,D_00442240);
 func_00166BD8(tile,0x46,1,0xE);
 func_00166E90(tile,0x4A,1);func_00166E90(tile,0x42,0x4A);func_00166E90(tile,0x47,0x31001);
 BUILDER *regionView=&region,*testView=&test;
 register BUILDER *frameView asm("$17")=&frame;
 register BUILDER *unmaskView asm("$19")=&unmask;
 register BUILDER *maskView asm("$23")=&mask;
 register BUILDER *restoreView asm("$18")=&restore;
 register BUILDER *enableView asm("$22")=&enable;
 for(;remaining>=0;remaining-=0x20){
  {register BUILDER *argument asm("$4");register BUILDER *input asm("$fp")=coordinates;asm("daddu %0,%1,$zero":"=r"(argument):"r"(input));func_00166E90(argument,5,0x79000000L|first);}first+=0x200;
  {register BUILDER *argument asm("$4");register BUILDER *input asm("$fp")=coordinates;asm("daddu %0,%1,$zero":"=r"(argument):"r"(input));func_00166E90(argument,5,0x87000000L|second);}second+=0x200;
 }
 func_00166E90(&tiles,0x4A,0);func_00166E90(&tiles,0x42,0x44);func_00166E90(&tiles,0x47,0x50000);
 func_00166968(&tiles);
 func_00166920(frameView);
 ulong *active=(D_002EDDB0&1)?&D_002EDCE0:&D_002EDBF0;
 register ulong frameWord asm("$16")=*active;
 func_00157330(frameView,3,D_00442210);
 func_00166BD8(frameView,0,1,0xE);func_00166E90(frameView,0x3F,0);func_00166E90(frameView,0x4E,0x3A000000L|(frameWord&0x1FF));
 func_00166968(frameView);
 func_00166920(unmaskView);
 func_00157330(unmaskView,2,D_004424B0);
 func_00166BD8(unmaskView,0,1,0xE);func_00166E90(unmaskView,0x4C,0);func_00166968(unmaskView);
 func_00166920(maskView);
 func_00157330(maskView,2,D_004424D0);
 func_00166BD8(maskView,0,1,0xE);func_00166E90(maskView,0x4C,0xFF00000000000000UL);func_00166968(maskView);
 func_00166920(restoreView);
 func_00157330(restoreView,4,D_00442560);
 func_00166BD8(restoreView,0,1,0xE);func_00166E90(restoreView,0x4A,0);func_00166E90(restoreView,0x42,0x44);func_00166E90(restoreView,0x47,0x50000);func_00166968(restoreView);
 func_00166920(regionView);
 func_00157330(regionView,3,D_004425A0);
 func_00166BD8(regionView,0,1,0xE);func_00166E90(regionView,0x42,0x44);func_00166E90(regionView,0x47,0x74000);func_00166968(regionView);
 func_00166920(testView);
 func_00157330(testView,3,D_004424F0);
 func_00166BD8(testView,0,1,0xE);func_00166E90(testView,0x42,0x4A);func_00166E90(testView,0x47,0x30000);func_00166968(testView);
 func_00166920(enableView);
 func_00157330(enableView,4,D_00442520);
 func_00166BD8(enableView,0,1,0xE);func_00166E90(enableView,0x4A,1);func_00166E90(enableView,0x42,0x4A);func_00166E90(enableView,0x47,0x31001);func_00166968(enableView);
}
