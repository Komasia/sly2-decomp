// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* Float tangent kernel, adapted from newlib kf_tan.c.
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this software is freely
 * granted, provided that this notice is preserved.
 */
typedef union {float value;unsigned word;} FLOATWORD;
#define GET_FLOAT_WORD(i,d) do {FLOATWORD u;u.value=(d);(i)=u.word;}while(0)
#define SET_FLOAT_WORD(d,i) do {FLOATWORD u;u.word=(i);(d)=u.value;}while(0)
extern const float D_002AC0F8[];
float func_00244EF8(float);
float __kernel_tanf(float x,float y,int iy)
{
 float z,r,v,w,s;
 int ix,hx;
 GET_FLOAT_WORD(hx,x);ix=hx&0x7FFFFFFF;
 if(ix<0x31800000){if((int)x==0){
  if((ix|(iy+1))==0)return 1.0f/func_00244EF8(x);
  else return iy==1?x:-1.0f/x;
 }}
 if(ix>=0x3F2CA140){
  if(hx<0){x=-x;y=-y;}
  z=7.8539812565e-01f-x;w=3.7748947079e-08f-y;
  x=z+w;y=0.0f;
 }
 z=x*x;w=z*z;
 r=D_002AC0F8[1]+w*(D_002AC0F8[3]+w*(D_002AC0F8[5]+w*(D_002AC0F8[7]+w*(D_002AC0F8[9]+w*D_002AC0F8[11]))));
 v=z*(D_002AC0F8[2]+w*(D_002AC0F8[4]+w*(D_002AC0F8[6]+w*(D_002AC0F8[8]+w*(D_002AC0F8[10]+w*D_002AC0F8[12])))));
 s=z*x;r=y+z*(s*(r+v)+y);r+=D_002AC0F8[0]*s;w=x+r;
 if(ix>=0x3F2CA140){v=(float)iy;return (float)(1-((hx>>30)&2))*(v-2.0f*(x-(w*w/(w+v)-r)));}
 if(iy==1)return w;
 else{
  float a,t;int i;
  z=w;GET_FLOAT_WORD(i,z);SET_FLOAT_WORD(z,i&0xFFFFF000);
  v=r-(z-x);t=a=-1.0f/w;
  GET_FLOAT_WORD(i,t);SET_FLOAT_WORD(t,i&0xFFFFF000);
  s=1.0f+t*z;return t+a*(s+t*v);
 }
}
