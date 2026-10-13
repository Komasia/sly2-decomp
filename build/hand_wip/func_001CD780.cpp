// Project a world label, fit its rectangle, and render it in the supplied color.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
struct RGBA {unsigned char r,g,b,a;RGBA(){}RGBA(uint bits){*(uint*)this=bits;}};
struct CM {char pad40[0x40];float sx,sy,unknown,nearDepth;char pad50[0x10];qword matrix[4];};
struct LM {float low,high;};
struct RT {const char *text;char *current;void *font,*baseFont,*alternateFont;RGBA color,baseColor,alternateColor;char pad20[0x20];qword color0,color1;int changed;float cameraX,cameraY,offsetX,offsetY,width,height,sx,sy,lineHeight,fontScale;int vAlign,hAlign,priority;};
struct CONFIG;
extern "C" void func_00258438(CONFIG *,float,float);
extern "C" void func_00258448(CONFIG *,float,float);
extern "C" void func_00258458(CONFIG *,const RGBA *);
extern "C" void func_00258470(CONFIG *,int);
extern "C" void func_00258478(CONFIG *,int);
struct CONFIG {float x,y,width,height;RGBA color;int hAlign,vAlign;CONFIG(uint bits=0xFF808080){func_00258438(this,0.0f,0.0f);func_00258448(this,640.0f,492.8000183f);RGBA gray(bits);func_00258458(this,&gray);func_00258470(this,0);func_00258478(this,0);}};
extern CM D_002DDF40;
extern float D_002C1F20;
extern LM D_002C1F28;
extern int D_002C1F30,D_002C1F34;
extern "C" qword func_0014F308(CM *,qword);
extern "C" float func_0011D948(LM *,float);
extern "C" RT *func_00215AC0(RT *,const char *,float);
extern "C" void func_00216260(RT *,float *,float *);
extern "C" void func_002163B0(RT *,CONFIG *,int);
static inline float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline float Y(qword q){float f;__asm__("prot3w %0,%1":"=r"(f):"r"(q));return f;}
static inline float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
extern "C" void func_001CD780(qword position,const char *text,int unused,const RGBA *color,float height)
{
    CM *camera=&D_002DDF40;
    qword screen=func_0014F308(camera,position);
    float depth=Z(screen);
    if(depth<camera->nearDepth)return;
    float scale=func_0011D948(&D_002C1F28,height*(D_002C1F20/(camera->sx*depth)));
    RT rt;func_00215AC0(&rt,text,scale);
    float dimensions[2];
    CONFIG config;
    func_00216260(&rt,&dimensions[0],&dimensions[1]);
    float x=(X(screen)*0.5f+0.5f)*640.0f;
    float y=(0.5f-Y(screen)*0.5f)*492.8000183f;
    int marginX=D_002C1F30,marginY=D_002C1F34;
    config.x=x-dimensions[0]*0.5f-marginX;
    config.y=y-dimensions[1]-2*marginY;
    config.width=dimensions[0]+2*marginX;
    config.height=dimensions[1]+2*marginY;
    config.x+=marginX;config.y+=marginY;
    RGBA rgba=*color;config.color=rgba;
    func_002163B0(&rt,&config,6);
}
