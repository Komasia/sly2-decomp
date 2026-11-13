struct P {int tag,value,word8;void *vtable;};
struct REF {int tag,value;};
void *s1_memset(void*,int,unsigned int);
void func_002562A8(struct REF*);
extern char D_002D04A0[];
extern char D_002D0AB0[];
extern char D_002D0A30[];
extern char D_002D07B0[];
extern char D_002D0930[];
extern char D_002D0830[];
extern char D_002D08B0[];
extern char D_002D0620[];
extern char D_002D05A0[];
extern char D_002D06A0[];
extern char D_002CF7F8[];
extern char D_002D0520[];
extern char D_002CFA10[];
extern char D_002D4AF8[];
extern char D_002D0320[];
extern char D_002D02A0[];
extern char D_002D0420[];
extern char D_002D03A0[];
extern char D_002D0220[];
extern char D_002D01A0[];
extern char D_002D0120[];
extern char D_002CDDC0[];
extern char D_002CDD40[];
extern char D_002CC4C0[];
extern char D_002CC440[];
extern char D_002CC3C0[];
extern char D_002CC340[];
extern char D_002CC2C0[];
extern char D_002CC240[];
extern char D_002CCE90[];
extern char D_002CC1C0[];
extern char D_002D00A0[];
extern char D_002D0020[];
extern char D_002CFFA0[];
extern char D_002CFF20[];
extern char D_002CFE20[];
extern char D_002CFD20[];
extern char D_002CFCA0[];
extern char D_002CFC20[];
extern char D_002CFDA0[];
// name: SafeHouse port (PjobNew)
struct P *PjobNew__F3CIDPv(int kind,void *memory){
 struct P *result;
 switch(kind){
 case 0x9C:
  s1_memset(memory,0,0xB0);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D04A0;
  s1_memset((char*)memory+0x30,0,0x70);
  result=(struct P*)memory;break;
 case 0x9D:
  s1_memset(memory,0,0x50);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D0AB0;
  result=(struct P*)memory;break;
 case 0x9E:
  s1_memset(memory,0,0x50);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D0A30;
  result=(struct P*)memory;break;
 case 0x9F:
  s1_memset(memory,0,0x60);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D07B0;
  result=(struct P*)memory;break;
 case 0xA1:
  s1_memset(memory,0,0xC0);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D0930;
  result=(struct P*)memory;break;
 case 0xA2:
  s1_memset(memory,0,0xC0);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D0830;
  result=(struct P*)memory;break;
 case 0xA3:
  s1_memset(memory,0,0xC0);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D08B0;
  result=(struct P*)memory;break;
 case 0xA4:
  s1_memset(memory,0,0x50);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D0620;
  result=(struct P*)memory;break;
 case 0xA5:
  s1_memset(memory,0,0x60);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D05A0;
  result=(struct P*)memory;break;
 case 0xA7:
  s1_memset(memory,0,0xF0);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D06A0;
  result=(struct P*)memory;break;
 case 0xA9:
  s1_memset(memory,0,0x60);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CF7F8;
  result=(struct P*)memory;break;
 case 0xAA:
  s1_memset(memory,0,0x50);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D0520;
  result=(struct P*)memory;break;
 case 0xAB:
  s1_memset(memory,0,0xE0);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CFA10;
  result=(struct P*)memory;break;
 case 0xAE:
  s1_memset(memory,0,0x40);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D4AF8;
  result=(struct P*)memory;break;
 case 0xAC:
  s1_memset(memory,0,0xA0);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D0320;
  result=(struct P*)memory;break;
 case 0xAF:
  s1_memset(memory,0,0x60);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D02A0;
  result=(struct P*)memory;break;
 case 0xB0:
  s1_memset(memory,0,0x40);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D0420;
  result=(struct P*)memory;break;
 case 0xB1:
  s1_memset(memory,0,0x70);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D03A0;
  result=(struct P*)memory;break;
 case 0xAD:
  s1_memset(memory,0,0x40);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D0220;
  result=(struct P*)memory;break;
 case 0xB2:
  s1_memset(memory,0,0x50);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D01A0;
  result=(struct P*)memory;break;
 case 0xB3:
  s1_memset(memory,0,0x40);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D0120;
  result=(struct P*)memory;break;
 case 0xB4:
  s1_memset(memory,0,0x40);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CDDC0;
  result=(struct P*)memory;break;
 case 0xB5:
  s1_memset(memory,0,0x60);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CDD40;
  result=(struct P*)memory;break;
 case 0xA8:
  s1_memset(memory,0,0xE0);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CC4C0;
  result=(struct P*)memory;break;
 case 0xC1:
  s1_memset(memory,0,0x50);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CC440;
  result=(struct P*)memory;break;
 case 0xC2:
  s1_memset(memory,0,0xA0);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CC3C0;
  result=(struct P*)memory;break;
 case 0xC3:
  s1_memset(memory,0,0x40);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CC340;
  result=(struct P*)memory;break;
 case 0xC4:
  s1_memset(memory,0,0x40);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CC2C0;
  result=(struct P*)memory;break;
 case 0xC5:
  s1_memset(memory,0,0x40);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CC240;
  result=(struct P*)memory;break;
 case 0xB6:
  s1_memset(memory,0,0x50);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CCE90;
  result=(struct P*)memory;break;
 case 0xC6:
  s1_memset(memory,0,0x40);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CC1C0;
  result=(struct P*)memory;break;
 case 0xB7:
  s1_memset(memory,0,0x70);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D00A0;
  result=(struct P*)memory;break;
 case 0xB8:
  s1_memset(memory,0,0x40);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002D0020;
  result=(struct P*)memory;break;
 case 0xB9:
  s1_memset(memory,0,0x40);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CFFA0;
  result=(struct P*)memory;break;
 case 0xBB:
  s1_memset(memory,0,0x30);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CFF20;
  result=(struct P*)memory;break;
 case 0xBA:
  s1_memset(memory,0,0xD0);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CFE20;
  func_002562A8((struct REF*)((char*)memory+0x40));
  func_002562A8((struct REF*)((char*)memory+0x60));
  func_002562A8((struct REF*)((char*)memory+0x80));
  result=(struct P*)memory;break;
 case 0xBD:
  s1_memset(memory,0,0x50);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CFD20;
  result=(struct P*)memory;break;
 case 0xBE:
  s1_memset(memory,0,0x50);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CFCA0;
  result=(struct P*)memory;break;
 case 0xBF:
  s1_memset(memory,0,0x50);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CFC20;
  func_002562A8((struct REF*)((char*)memory+0x30));
  result=(struct P*)memory;break;
 case 0xC0:
  s1_memset(memory,0,0x60);
  ((struct P*)memory)->tag=0;((struct P*)memory)->value=0;((struct P*)memory)->vtable=D_002CFDA0;
  result=(struct P*)memory;break;
 default:break;
 }
 return result;
}
