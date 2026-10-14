#include "vifs.h"
#include "bis.h"
struct OWNER;struct D;struct E;struct FACE;struct OBJECT;struct MATERIAL;struct SKIN;struct SKINROW;struct RECHEAD;struct SPHERE;
struct V3{float x,y,z;} __attribute__((packed));
struct UV{float u,v;} __attribute__((packed));
struct POS{V3 xyz;float w;};
struct COLOR{uchar r,g,b,a;} __attribute__((packed));
struct PACK{uchar u0,u1,v0,v1,link0,link1;} __attribute__((packed));
struct UVSHORT{ushort u,v;};
struct CACHED{ushort first,second;uchar extra,pad;};
struct BUFFER{int count;CACHED*data;};
struct CACHE{int count;BUFFER*buffers;int*indices;};
struct VE{short delta,pad;int(*fn)(void*,OBJECT*,MATERIAL*);};
struct MATERIAL{char pad0[12];VE*vt;char pad10[16];uint flags;char pad24[32];int words;QW*copy;};
struct OBJECT{char pad0[4];uchar kind,subtype;char pad6[2];COLOR tint;char padC[8];ushort textureScale;char pad16[6];int segmentCount;void*segments;ushort property;char pad26[2];MATERIAL*override;};
struct D{char kind,count,flags,pad3;float radius;QW*chain;int base,words;};
struct TRANSFORM{char pad0[64];MATRIX4 world;};
struct BONE{int value;char pad4[4];int index;TRANSFORM*transform;MATRIX4 local;};
struct E{int unknown;TRANSFORM*transform;void*parent;uint flags;QW*chain;int base;BONE*bones;SKIN*skin;MATERIAL*override;SPHERE*sphere;};
struct LIST{SKINROW*first,*last;int stride;};
struct SKIN{int owner;E*entry;int tag;void*context;int count,first,second;ushort flags,pad1E;int base;char pad24[12];int kind;float coefficient[4];char pad44[12];MATRIX4 frame;LIST rows;SKIN*next;char padA0[16];};
struct SKINROW{int count;POS*positions;POS*outputs[4];SKINROW*next;};
struct REC{int count;uint flags;UVSHORT*uv;POS*positions;PACK*packed;COLOR*rgba,*normal;int zero;};
struct RECHEAD{D*descriptor;int total;REC*records;RECHEAD*next;};
struct OWNER{int owner;char pad4[32];int objectCount;MATERIAL**objects;int extraCount;int*ownerIDs;char pad34[24];int stamp;ulong flags;SKIN*skin;RECHEAD*saved;};
struct PARAM{float value;int words,kind;};
struct FACE{int count;OBJECT*object;uint flags;MATERIAL*override;int unique;int*indices;POS*positions;UVSHORT*uv;PACK*packed;ushort*colors,*secondColors;uchar*alpha,*extra;COLOR*rgba,*normal;uchar*weights;};
struct REMAP{int vertex;FACE*destination;int destinationIndex;FACE*source;int sourceIndex;} __attribute__((packed));
struct ROW{ushort position,normSplit,end,countFlags;ushort segments[3],extra;ushort reordered,remap,override,pad16,textureScale,uvAux,weights,property;};
struct HEADER{ushort unknown,entry,extra,special,flags,base,skinFlags,skinBase;ushort bones[4];ROW rows[2];};
struct CURVE{V3 position;float unknownC;UV slope;int kind,direct;V3 offset;float unknown2C;} __attribute__((aligned(16)));
struct JOB{uint positions,rgba,normals,alpha,extra;ushort*colors,*secondColors;float scale;uchar*outAlpha,*outExtra;};
struct INPUT{int count,material;uint flags;};
union PACKET{QW params;INPUT input;COLOR color;};
struct REQUEST{int bytes,alignment;REQUEST(int b,int a):bytes(b),alignment(a){}};
union TEMP{SKIN skin;uchar builder[sizeof(VIFS)];};
extern "C"{
void*func_001AE478(void*);void func_001AE4A0(void*,int);
void*func_001AE1D0(const REQUEST&);void*func_001AE238(const REQUEST&,const void*);void*func_001AE2A0(const REQUEST&);void*func_001AE318(const REQUEST&);void*func_001AE378(const REQUEST&);
void func_001AE5A0(void*,const void*,uint);
void func_0011A050(LIST*,int);void func_0011A070(LIST*,SKINROW*,E*);
int func_00132B10(int,int);void func_0014E270(void*,float*,float);
CACHE*func_0016C8E0(OWNER*,CBinaryInputStream*);
void func_001699E8(OWNER*,D*,E*,SPHERE*,int,int,const int*,FACE**,CBinaryInputStream*);
void func_00169EB8(D*,E*,int,QW*,int,QW*,QW*);
int func_001EC688(OBJECT*,int,int,VIFS*);int func_001EC6D0(OBJECT*,int,int,VIFS*);void func_001EC740(int,int,int,QW*,QW*);
OBJECT*func_001EC820(int);OBJECT*func_001EC8F8(int);void func_001ED278(COLOR*);int func_001ED960(MATERIAL*,int,VIFS*);
VIFS*func_00226C10(VIFS*);void*func_002333B4(void*,int,uint);void func_002338C0(void*,uint,uint,int(*)(const void*,const void*));int func_00169988(const void*,const void*);
extern char D_002DDF40[];extern float D_002A52A0;extern int D_003E12D0,D_003DA790,D_002DEB54,D_002BE580,D_003E11EC;
extern QW D_002DEB60;extern uint D_002BE540[];extern UPK D_002BE558[];
extern char D_00000000[],D_00000010[],D_00003628[],D_000037A8[],D_00002E20[],D_00002EF8[],D_00002E68[],D_00002F80[],D_00002EB0[],D_00002FC8[],D_00002EE8[],D_00003358[];
}
struct MARK{MARK(){func_001AE478(this);}~MARK(){func_001AE4A0(this,2);}};
struct LEASE{LEASE(){func_001AE478(this);}void Release(){func_001AE4A0(this,2);}};
static inline void*Allocate(int bytes){return func_001AE2A0(REQUEST(bytes,16));}
static inline void*Raw(int bytes){return func_001AE318(REQUEST(bytes,16));}
static inline void*Zero(int bytes){return func_001AE378(REQUEST(bytes,16));}
static inline void*Copy(int bytes,const void*data){return func_001AE238(REQUEST(bytes,16),data);}
static inline int Accept(MATERIAL*p,OBJECT*object){VE e=p->vt[10];return e.fn((char*)p+e.delta,object,p);}
static inline void Unpack(VIFS*p,UPK kind,int count,int address,void*out){p->UnpackHelper(kind,count,address,0,(uint**)out);}
static inline int Round(float value){float word;int result;asm("cvt.w.s %0,%1":"=f"(word):"f"(value));asm("mfc1 %0,%1":"=r"(result):"f"(word));return result;}
static inline uint Relocate(uint value,int words,QW*old,QW*copy){if(value&&(value>=(uint)old)&&(value<(uint)old+words*16))value+=(uint)copy-(uint)old;return value;}
extern "C" void func_0016A000(OWNER*owner,D*desc,E*entry,PARAM*param,SPHERE*spheres,int groups,CBinaryInputStream*stream){
 desc->flags=stream->U8Read();
 int selected=stream->S16Read();
 if(selected>=0)entry->override=owner->objects[selected];
 if(desc->flags&1)entry->flags|=0x100;
 if(desc->flags&2)entry->flags|=0x200;
 MARK outer;
 VIFS main,aux;
 main.AllocSw(0x2000);
 QW*last=(QW*)main.m_pb;
 entry->flags=(entry->flags&0xFFC01FFF)|((D_003DA790&0x1FF)<<13);
 PACKET value;
 if(!(desc->flags&1)){
  aux.AllocSw(0x800);
  if(func_00132B10(owner->owner,0x31)){
   if(!(desc->flags&4)&&(uint)((uchar)desc->kind-7)>=2&&desc->radius==D_002A52A0){
    if(D_003E12D0==0){
     value.params.an[2]=0;value.params.ag[1]=1;entry->flags|=0x1000;value.params.ag[0]=1;value.params.an[3]=0;
     aux.AddDmaCnt();aux.AddVifUnpack(UPK_V4_32,4,&entry->transform->world,0);aux.AddVifUnpack(UPK_V4_32,1,&value.params,8);aux.EndDmaCnt();
    }
   }
  }
 }else{main.AddDmaCnt();owner->flags|=1UL<<32;}
 float*environment;
 Unpack(&main,UPK_V4_32,1,9,&environment);
 func_0014E270(D_002DDF40,environment,param->value);
 desc->count=stream->U8Read();entry->bones=(BONE*)Allocate(desc->count*80);
 for(int i=0;i<desc->count;i++){BONE*bone=entry->bones+i;bone->value=stream->S32Read();bone->index=stream->S16Read();}
 int base=(desc->flags&1)?0x21:0x15;
 if(desc->count){desc->base=base;base+=desc->count*4;}
 CURVE curve;
 curve.kind=stream->S8Read();
 if(curve.kind!=-1){stream->ReadCb12(&curve.position);stream->ReadCb8(&curve.slope);stream->ReadVector((VECTOR*)&curve.offset);curve.position.y*=0.007874016f;curve.position.z*=0.00006200012f;curve.direct=desc->flags&1;}
 CACHE*cache=func_0016C8E0(owner,stream);
 TEMP temp;
 if(desc->flags&4){
  SKIN*init=&temp.skin;func_002333B4(init,0,176);init->tag=stream->S32Read();init->kind=stream->S8Read();
  if(init->kind!=-1){init->coefficient[0]=stream->F32Read();init->coefficient[1]=stream->F32Read();init->coefficient[2]=stream->F32Read();init->coefficient[3]=stream->F32Read();stream->ReadMatrix4(&init->frame);}
  init->count=stream->U8Read();init->first=stream->U8Read();init->second=stream->U8Read();
  SKIN*skin=(SKIN*)Copy(176,init);skin->owner=owner->owner;skin->flags=(ushort)skin->count;skin->entry=entry;
  if(skin->first)skin->flags|=0x100;
  if(skin->second)skin->flags|=0x200;
  func_0011A050(&skin->rows,24);skin->base=base;
  if(skin->first)base+=skin->count*4;
  if(skin->second)base+=skin->count*4;
  entry->skin=skin;skin->next=owner->skin;owner->skin=skin;
 }
 int jobsCount=0;
 int partCount=stream->S16Read();
 VIFS*cpu=(VIFS*)temp.builder;func_00226C10(cpu);
 if(!(desc->flags&1)){cpu->AllocSw(0x2000);cpu->AddDmaCnt();}
 int*counts=(int*)Zero(partCount*4);FACE**parts=(FACE**)Zero(partCount*4);
 JOB*jobs[1024];
 int mainWords;QW*oldMain,*copyMain;
 for(int part=0;part<partCount;part++){
  int faceCount=stream->U8Read();FACE*faces=(FACE*)Zero(faceCount*64);counts[part]=faceCount;parts[part]=faces;
  HEADER*header;Unpack(&main,UPK_V4_16,11,10,&header);func_002333B4(header,0,88);
  switch(part){case 0:header->flags=1;switch(param->kind){case 0:header->flags|=0x100;break;case 1:header->flags|=0x200;break;case 2:header->flags|=0x400;break;}break;case 1:header->flags=4;break;}
  header->entry=(ushort)entry->unknown;
  if(desc->flags&1)header->flags|=2;
  if(desc->flags&16)header->flags|=128;
  if(entry->skin){header->skinFlags=entry->skin->flags;header->skinBase=(ushort)entry->skin->base;}
  if(desc->count)header->skinBase=(ushort)desc->base;
  int total=0;
  for(int f=0;f<faceCount;f++){
   FACE*face=faces+f;stream->Read(12,&value.input);face->count=value.input.count;face->object=func_001EC8F8(value.input.material);face->flags=value.input.flags;
   MATERIAL*material=entry->override;
   if(material&&Accept(material,face->object))face->override=entry->override;
   if(face->override==0){material=face->object->override;if(material&&Accept(material,face->object))face->override=face->object->override;}
   if(face->override){if(face->override->flags&1)face->flags|=16;if(face->override->flags&2)face->flags|=8;}
   if(face->flags&32)face->indices=(int*)Zero(face->count*4);
   total+=face->count;
   if(D_002DEB54)face->flags&=~2;
   switch(face->object->kind){case 3:face->flags|=6;break;case 7:if(!(face->object->subtype&32))face->flags|=4;break;}
  }
  LEASE inner;
  int vertices=stream->U8Read();
  V3*positions=(V3*)Raw(vertices*12);stream->Read(vertices*12,positions);
  UV*uv=(UV*)Raw(vertices*8);stream->Read(vertices*8,uv);
  V3*normals=(V3*)Raw(vertices*12);stream->Read(vertices*12,normals);
  COLOR*colors=(COLOR*)Raw(vertices*4);stream->Read(vertices*4,colors);
  for(COLOR*c=colors;(uint)c<(uint)(colors+vertices);c++)func_001ED278(c);
  int alpha=stream->S8Read();if(desc->kind<9&&desc->kind>=3)alpha=1;
  uchar*weights;
  if(desc->count){
   for(int k=0;k<4;k++)header->bones[k]=(ushort)desc->base+stream->U8Read()*4;
   int n=desc->count<=3?desc->count:4;weights=(uchar*)Raw(n*vertices);stream->Read((desc->count<=3?desc->count:4)*vertices,weights);
  }else weights=0;
  uchar*indices=(uchar*)Raw(total);stream->Read(total,indices);
  int flagBytes=((total+31)/32)*4;uint*flagWord=(uint*)Raw(flagBytes);stream->Read(flagBytes,flagWord);uint flagMask=1;
  int useRemap=0;if((desc->flags&5)||desc->count||curve.kind!=-1)useRemap=1;
  int simple=0;if(!useRemap&&faces[0].override==0)simple=faces[1].override==0;
  int current=base;header->base=current;
  REMAP*remap;
  if(desc->count==0&&!(desc->flags&1)&&curve.kind==-1)remap=0;
  else if(desc->flags&8){
   remap=(REMAP*)Raw(total*20);REMAP*out=remap;uchar*in=indices;
   for(int f=0;f<faceCount;f++){FACE*face=faces+f;face->unique=0;for(int v=0;v<face->count;v++){out->destinationIndex=v;out->sourceIndex=v;out->vertex=*in++;out->source=face;out->destination=face;out++;}}
  }else{
   REMAP**seen=(REMAP**)Zero(vertices*4);remap=(REMAP*)Raw(total*20);REMAP*out=remap;
   for(int f=0;f<faceCount;f++)faces[f].unique=faces[f].count;
   uchar*in=indices+total;FACE*destination=faces+faceCount-1;
   for(int f=faceCount-1;f>=0;f--){
    FACE*source=faces+f;
    for(int v=source->count-1;v>=0;v--){
     int vertex=*--in;REMAP*old=seen[vertex];
     if(old==0){out->destination=destination;out->vertex=vertex;out->destinationIndex=--destination->unique;seen[vertex]=out;if(destination->unique==0)destination--;}
     else *out=*old;
     out->sourceIndex=v;out->source=source;out++;
    }
    if(!useRemap){destination=faces+f-1;func_002333B4(seen,0,vertices*4);}
   }
   func_002338C0(remap,total,20,func_00169988);
  }
  if(curve.kind!=-1){header->rows[0].pad16=base;header->rows[1].pad16=base;main.AddVifUnpack(UPK_V4_32,3,&curve,base);current=base+3;}
  uchar*vertexIndices=indices;
  for(int f=0;f<faceCount;f++){
   FACE*face=faces+f;ROW*row=header->rows+f;
   row->countFlags=(ushort)face->count|0x8000;row->textureScale=face->object->textureScale;row->property=face->object->property;
   for(int j=0;j<3;j++)for(int i=0;i<f;i++){if(face->object==faces[i].object&&((face->flags>>j)&1)&&((faces[i].flags>>j)&1)){row->segments[j]=header->rows[i].segments[j];break;}}
   for(int j=0;j<3;j++)if(row->segments[j]==0&&((face->flags>>j)&1)){
    if(desc->flags&2)for(int i=owner->extraCount-1;i>=0;i--)current+=func_001EC6D0(func_001EC820(owner->ownerIDs[i]),j,current,&main);
    row->segments[j]=current;current+=func_001EC688(face->object,j,current,&main);
   }
   if(face->override){
    for(int i=0;i<f;i++)if(face->override==faces[i].override){row->override=header->rows[i].override;break;}
    if(row->override==0){row->override=current;current+=func_001ED960(face->override,current,&main);}
   }
   int position=current+1;row->position=position;current=position+face->count*4;row->end=current;row->normSplit=position+(((face->count/2&~3)+2)*4);
   if(remap)row->reordered=position+face->unique*4;
   if(desc->count){row->weights=current;current+=face->count-face->unique;header->flags|=(desc->flags&1)?32:16;}
   if(face->object->kind==3&&header->special==0){
    header->rows[0].extra=current;header->rows[1].extra=current;current+=func_001EC688(face->object,3,current,&main);
    ushort*out;Unpack(&main,UPK_S16,1,current,&out);*out=current+2;header->special=current;current+=26;
   }
   if(curve.kind!=-1){if(!(desc->flags&1)){row->uvAux=current;int n=face->count-face->unique;Unpack(&main,(UPK)0x1E,n,(ushort)current,&face->normal);current+=n;}else row->uvAux=row->reordered+1;}
   if(entry->skin){row->weights=current;header->flags|=64;current+=entry->skin->count*face->count;}
   main.AddVifStcycl(1,4);
   if((desc->flags&1)||desc->count||curve.kind!=-1)Unpack(&main,(UPK)0x19,face->count,row->position,&face->packed);
   else Unpack(&main,(UPK)0x15,face->count,row->position,&face->uv);
   if(desc->flags&1){
    if(face->unique<face->count){Unpack(&main,(UPK)0x1E,face->count-face->unique,row->reordered+1,&face->normal);Unpack(&main,UPK_V4_8,face->count-face->unique,row->reordered+2,&face->rgba);}
   }else{
    main.Align(0);aux.AddDmaRefs(((int)(main.m_pb-(uchar*)last))>>4,last);last=(QW*)main.m_pb;aux.AddDmaCnt();
    Unpack(&aux,UPK_V4_5,face->count,row->position+1,&face->colors);
    if((face->flags&2)&&face->object->kind!=3)Unpack(&aux,UPK_V4_5,face->count,row->position+2,&face->secondColors);
    if(alpha||face->secondColors){
     aux.AddVifStmask(0x3F3F3F3F);
     if(alpha)Unpack(&aux,UPK_S8,face->count,row->position+1,&face->alpha);
     if(face->secondColors)Unpack(&aux,UPK_S8,face->count,row->position+2,&face->extra);
     aux.AddVifStmask(0);
    }
    aux.EndDmaCnt();
   }
   Unpack(&main,UPK_V4_32,face->count,row->position+3,&face->positions);main.AddVifStcycl(1,1);
   if(desc->count&&face->unique<face->count){
    if(desc->count<4){main.AddVifStrow(&D_002DEB60);main.AddVifStmask(D_002BE540[desc->count<=3?desc->count:4]);}
    Unpack(&main,D_002BE558[desc->count<=3?desc->count:4],face->count-face->unique,row->weights,&face->weights);
    if(desc->count<4)main.AddVifStmask(0);
   }
   if(entry->skin){
    ushort address=row->weights;SKINROW*skinRow=(SKINROW*)Allocate(28);func_0011A070(&entry->skin->rows,skinRow,entry);skinRow->count=face->count;skinRow->positions=face->positions;
    for(int i=0;i<entry->skin->count;i++){Unpack(&main,UPK_V4_32,face->count,address,&skinRow->outputs[i]);func_002333B4(skinRow->outputs[i],0,face->count*16);address+=face->count;}
   }
   if(!(desc->flags&1)){
    if(face->object->kind!=1&&face->object->kind!=7){
     ushort*out=face->colors;uchar*outAlpha=face->alpha;
     for(int v=0;v<face->count;v++){
      value.color=colors[vertexIndices[v]];COLOR&color=value.color;*(COLOR*)&temp.skin.kind=face->object->tint;COLOR&tint=*(COLOR*)&temp.skin.kind;uint a=((color.a*tint.a+255)/510)&255;
      uint packed=((((color.r*tint.r+255)/256)>>3)&31)|(((((color.g*tint.g+255)/256)>>3)&31)<<5)|(((((color.b*tint.b+255)/256)>>3)&31)<<10)|((a>>7)<<15);
      *out++=packed;if(outAlpha)*outAlpha++=a;
     }
    }else if(D_002BE580||!(face->flags&32)){
     for(int start=0;start<face->count;start+=39){
      int n=face->count-start;if(n>39)n=39;
      JOB*job;Unpack(cpu,UPK_V4_32,3,0x307,&job);
      job->positions=0x30A;job->rgba=job->positions+n*3;job->normals=job->rgba;job->alpha=job->normals+n;job->extra=job->alpha+n;
      job->colors=(ushort*)((char*)face->colors+start*2);job->secondColors=(ushort*)((char*)face->secondColors+start*2);job->outAlpha=alpha?(uchar*)((char*)face->alpha+start):0;job->outExtra=(uchar*)((char*)face->extra+start);job->scale=face->object->textureScale*0.000244140625f;
      jobs[jobsCount++]=job;
      cpu->AddVifStcycl(1,3);
      V3*outNormal;COLOR*outColor;V3*outPosition;
      Unpack(cpu,UPK_V3_32,n,0x30A,&outNormal);Unpack(cpu,UPK_V4_8,n,0x30B,&outColor);Unpack(cpu,UPK_V3_32,n,0x30C,&outPosition);cpu->AddVifStcycl(1,1);
      for(int v=0;v<n;v++){
       int vertex=vertexIndices[start+v];*outNormal++=normals[vertex];*outPosition++=positions[vertex];value.color=colors[vertex];COLOR&color=value.color;*(COLOR*)&temp.skin.kind=face->object->tint;COLOR&tint=*(COLOR*)&temp.skin.kind;
       color.r=(color.r*tint.r+255)/256;color.g=(color.g*tint.g+255)/256;color.b=(color.b*tint.b+255)/256;color.a=(color.a*tint.a+255)/510;*outColor++=color;
      }
      cpu->AddVifMscal(D_00000010);AddDmaInt(cpu,0x90000000);
     }
    }
   }
   for(int v=0;v<face->count;v++){
    int vertex=vertexIndices[v];
    if(desc->count==0)face->positions[v].xyz=positions[vertex];else if(v<face->unique){face->positions[v].xyz.x=-1;face->positions[v].xyz.z=-1;face->positions[v].xyz.y=-1;}
    face->positions[v].w=(*flagWord&flagMask)?environment[0]+4096.0f:environment[0];flagMask<<=1;if(flagMask==0){flagMask=1;flagWord++;}
    if(face->packed){
     int u=Round(uv[vertex].u*4096.0f+0.5f);face->packed[v].u0=u;face->packed[v].u1=u>>8;
     int w=Round(uv[vertex].v*4096.0f+0.5f);face->packed[v].v0=w;face->packed[v].v1=w>>8;
    }else{face->uv[v].u=Round(uv[vertex].u*4096.0f+0.5f);face->uv[v].v=Round(uv[vertex].v*4096.0f+0.5f);}
    if(face->flags&32){
     face->indices[v]=vertex;CACHED*saved=&cache->buffers[cache->indices[part]].data[vertex];face->colors[v]=saved->first;face->secondColors[v]=saved->second;face->extra[v]=saved->extra;
     if(face->alpha){value.color=colors[vertex];COLOR&color=value.color;*(COLOR*)&temp.skin.kind=face->object->tint;COLOR&tint=*(COLOR*)&temp.skin.kind;face->alpha[v]=(color.a*tint.a+255)/510;}
    }
   }
   vertexIndices+=face->count;
   if(!useRemap){
    if(f){if(desc->kind==11||desc->kind==13)main.AddVifMscal(D_000037A8);else main.AddVifMscal(simple?D_00002EE8:D_00003358);}
    else{
     main.AddVifMscal(D_00000000);
     if(desc->kind==11||desc->kind==13)main.AddVifMscal(D_00003628);
     else{void*code;switch(part){case 0:code=simple?D_00002E20:D_00002EF8;break;case 1:code=simple?D_00002E68:D_00002F80;break;default:code=simple?D_00002EB0:D_00002FC8;break;}main.AddVifMscal(code);}
    }
   }
  }
  if(useRemap){
   main.AddVifMscal(D_00000000);
   switch(desc->kind){case 11:case 13:main.AddVifMscal(D_00003628);main.AddVifMscal(D_000037A8);break;default:switch(part){case 0:main.AddVifMscal(D_00002EF8);break;case 1:main.AddVifMscal(D_00002F80);break;default:main.AddVifMscal(D_00002FC8);break;}main.AddVifMscal(D_00003358);break;}
  }
  if(remap){
   REMAP*end=remap+total;FACE*previous=0;
   for(REMAP*r=remap;(uint)r<(uint)end;r++){
    FACE*source=r->source;
    if(previous!=r->destination){previous=r->destination;header->rows[previous-faces].remap=header->rows[source-faces].position+r->sourceIndex*4;}
    uint next=0;
    if(r!=end-1&&r[1].destination==previous){next=header->rows[r[1].source-faces].position+r[1].sourceIndex*4;if(r->destinationIndex==r[1].destinationIndex)next|=0x8000;}
    source->packed[r->sourceIndex].link1=next>>8;source->packed[r->sourceIndex].link0=next;
   }
   REMAP*r=remap;
   while((uint)r<(uint)end){
    int vertex=r->vertex;FACE*face=r->destination;int destination=r->destinationIndex;value.color=colors[vertex];COLOR&color=value.color;
    uchar max=color.r;if(color.g>=color.r)max=color.g;if(color.b>=max)max=color.b;
    if(face->normal){COLOR*out=face->normal+destination-face->unique;int alpha=Round((float)max*0.003921569f*127.0f);out->r=Round(normals[vertex].x*127.0f);out->g=Round(normals[vertex].y*127.0f);out->a=alpha;out->b=Round(normals[vertex].z*127.0f);}
    if(face->rgba){*(COLOR*)&temp.skin.kind=face->object->tint;COLOR&tint=*(COLOR*)&temp.skin.kind;COLOR*out=face->rgba+destination-face->unique;out->r=(color.r*tint.r+255)/512;out->g=(color.g*tint.g+255)/512;out->b=(color.b*tint.b+255)/512;out->a=(color.a*tint.a+255)/510;}
    if(desc->count){face->positions[destination].xyz=positions[vertex];int n=desc->count>3?4:desc->count;func_001AE5A0(face->weights+(destination-face->unique)*n,weights+vertex*n,n);}
    do{r++;}while((uint)r<(uint)end&&r->destination==face&&r->destinationIndex==destination);
   }
  }
  inner.Release();
 }
 if(desc->flags&1){main.EndDmaCnt();main.AddDmaRet();main.DetachCopySw(&mainWords,&oldMain,&copyMain);desc->words=mainWords;entry->chain=copyMain;}
 else{
  main.Align(0);aux.AddDmaRefs(((int)(main.m_pb-(uchar*)last))>>4,last);aux.AddDmaRet();main.DetachCopySw(&mainWords,&oldMain,&copyMain);
  if(entry->override){entry->override->words=mainWords;entry->override->copy=copyMain;}
  func_00169EB8(desc,entry,(uint)(aux.m_pb-aux.m_ab)>>4,(QW*)aux.m_ab,mainWords,copyMain,oldMain);
  if(jobsCount>0){cpu->EndDmaCnt();cpu->AddDmaRet();param->words=(uint)(cpu->m_pb-cpu->m_ab)>>4;desc->chain=(QW*)Copy(param->words*16,cpu->m_ab);}
 }
 if(cache)owner->stamp=D_003E11EC;
 entry->flags=(entry->flags&0x803FFFFF)|((D_003DA790&0x1FF)<<22);
 func_001EC740((entry->flags>>13)&0x1FF,(entry->flags>>22)&0x1FF,mainWords*16,oldMain,copyMain);
 if(entry->skin){
  for(SKINROW*r=entry->skin->rows.first;r;r=r->next){
   if(&r->positions){uint address=(uint)r->positions;if(address>=(uint)oldMain&&address<(uint)oldMain+mainWords*16)r->positions=(POS*)(address+(uint)copyMain-(uint)oldMain);}
   for(int i=0;i<entry->skin->count;i++){POS**slot=&r->outputs[i];if(slot){uint address=(uint)*slot;if(address>=(uint)oldMain&&address<(uint)oldMain+mainWords*16)*slot=(POS*)(address+(uint)copyMain-(uint)oldMain);}}
  }
 }
 if(desc->flags&8){
  int total=0;for(int p=0;p<partCount;p++)total+=counts[p];RECHEAD*head=(RECHEAD*)Allocate(16);head->next=owner->saved;owner->saved=head;head->descriptor=desc;head->total=total;head->records=(REC*)func_001AE1D0(REQUEST(total*32,16));REC*out=head->records;
  for(int p=0;p<partCount;p++)for(int f=0;f<counts[p];f++){
   FACE*face=parts[p]+f;out->count=face->count;out->flags=face->flags;out->positions=(POS*)Relocate((uint)face->positions,mainWords,oldMain,copyMain);out->uv=(UVSHORT*)Relocate((uint)face->uv,mainWords,oldMain,copyMain);out->packed=(PACK*)Relocate((uint)face->packed,mainWords,oldMain,copyMain);out->rgba=(COLOR*)Relocate((uint)face->rgba,mainWords,oldMain,copyMain);out->normal=(COLOR*)Relocate((uint)face->normal,mainWords,oldMain,copyMain);out->zero=0;out++;
  }
 }
 func_001699E8(owner,desc,entry,spheres,groups,partCount,counts,parts,stream);
}

typedef char layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char layout_ulong[(sizeof(ulong)==8)?1:-1];
typedef char layout_QW[(sizeof(QW)==16)?1:-1];
typedef char layout_MATRIX4[(sizeof(MATRIX4)==64)?1:-1];
typedef char layout_VIFS[(sizeof(VIFS)==36)?1:-1];
typedef char layout_DMAS[(sizeof(DMAS)==28)?1:-1];
typedef char layout_stream[(sizeof(CBinaryInputStream)==52)?1:-1];
typedef char layout_jobs[(sizeof(JOB*[1024])==4096)?1:-1];
typedef char layout_V3_size[(sizeof(V3)==12)?1:-1];
typedef char layout_UV_size[(sizeof(UV)==8)?1:-1];
typedef char layout_POS_size[(sizeof(POS)==16)?1:-1];
typedef char layout_COLOR_size[(sizeof(COLOR)==4)?1:-1];
typedef char layout_PACK_size[(sizeof(PACK)==6)?1:-1];
typedef char layout_UVSHORT_size[(sizeof(UVSHORT)==4)?1:-1];
typedef char layout_CACHED_size[(sizeof(CACHED)==6)?1:-1];
typedef char layout_BUFFER_size[(sizeof(BUFFER)==8)?1:-1];
typedef char layout_CACHE_size[(sizeof(CACHE)==12)?1:-1];
typedef char layout_VE_size[(sizeof(VE)==8)?1:-1];
typedef char layout_MATERIAL_size[(sizeof(MATERIAL)==76)?1:-1];
typedef char layout_OBJECT_size[(sizeof(OBJECT)==44)?1:-1];
typedef char layout_D_size[(sizeof(D)==20)?1:-1];
typedef char layout_TRANSFORM_size[(sizeof(TRANSFORM)==128)?1:-1];
typedef char layout_BONE_size[(sizeof(BONE)==80)?1:-1];
typedef char layout_E_size[(sizeof(E)==40)?1:-1];
typedef char layout_LIST_size[(sizeof(LIST)==12)?1:-1];
typedef char layout_SKIN_size[(sizeof(SKIN)==176)?1:-1];
typedef char layout_SKINROW_size[(sizeof(SKINROW)==28)?1:-1];
typedef char layout_REC_size[(sizeof(REC)==32)?1:-1];
typedef char layout_RECHEAD_size[(sizeof(RECHEAD)==16)?1:-1];
typedef char layout_OWNER_size[(sizeof(OWNER)==96)?1:-1];
typedef char layout_PARAM_size[(sizeof(PARAM)==12)?1:-1];
typedef char layout_FACE_size[(sizeof(FACE)==64)?1:-1];
typedef char layout_REMAP_size[(sizeof(REMAP)==20)?1:-1];
typedef char layout_ROW_size[(sizeof(ROW)==32)?1:-1];
typedef char layout_HEADER_size[(sizeof(HEADER)==88)?1:-1];
typedef char layout_CURVE_size[(sizeof(CURVE)==48)?1:-1];
typedef char layout_JOB_size[(sizeof(JOB)==40)?1:-1];
typedef char layout_INPUT_size[(sizeof(INPUT)==12)?1:-1];
typedef char layout_PACKET_size[(sizeof(PACKET)==16)?1:-1];
typedef char layout_REQUEST_size[(sizeof(REQUEST)==8)?1:-1];
typedef char layout_TEMP_size[(sizeof(TEMP)==176)?1:-1];
typedef char layout_V3_x[((uint)&((V3*)0)->x==0)?1:-1];
typedef char layout_V3_y[((uint)&((V3*)0)->y==4)?1:-1];
typedef char layout_V3_z[((uint)&((V3*)0)->z==8)?1:-1];
typedef char layout_UV_u[((uint)&((UV*)0)->u==0)?1:-1];
typedef char layout_UV_v[((uint)&((UV*)0)->v==4)?1:-1];
typedef char layout_POS_xyz[((uint)&((POS*)0)->xyz==0)?1:-1];
typedef char layout_POS_w[((uint)&((POS*)0)->w==12)?1:-1];
typedef char layout_COLOR_r[((uint)&((COLOR*)0)->r==0)?1:-1];
typedef char layout_COLOR_g[((uint)&((COLOR*)0)->g==1)?1:-1];
typedef char layout_COLOR_b[((uint)&((COLOR*)0)->b==2)?1:-1];
typedef char layout_COLOR_a[((uint)&((COLOR*)0)->a==3)?1:-1];
typedef char layout_PACK_u0[((uint)&((PACK*)0)->u0==0)?1:-1];
typedef char layout_PACK_u1[((uint)&((PACK*)0)->u1==1)?1:-1];
typedef char layout_PACK_v0[((uint)&((PACK*)0)->v0==2)?1:-1];
typedef char layout_PACK_v1[((uint)&((PACK*)0)->v1==3)?1:-1];
typedef char layout_PACK_link0[((uint)&((PACK*)0)->link0==4)?1:-1];
typedef char layout_PACK_link1[((uint)&((PACK*)0)->link1==5)?1:-1];
typedef char layout_UVSHORT_u[((uint)&((UVSHORT*)0)->u==0)?1:-1];
typedef char layout_UVSHORT_v[((uint)&((UVSHORT*)0)->v==2)?1:-1];
typedef char layout_CACHED_first[((uint)&((CACHED*)0)->first==0)?1:-1];
typedef char layout_CACHED_second[((uint)&((CACHED*)0)->second==2)?1:-1];
typedef char layout_CACHED_extra[((uint)&((CACHED*)0)->extra==4)?1:-1];
typedef char layout_BUFFER_count[((uint)&((BUFFER*)0)->count==0)?1:-1];
typedef char layout_BUFFER_data[((uint)&((BUFFER*)0)->data==4)?1:-1];
typedef char layout_CACHE_count[((uint)&((CACHE*)0)->count==0)?1:-1];
typedef char layout_CACHE_buffers[((uint)&((CACHE*)0)->buffers==4)?1:-1];
typedef char layout_CACHE_indices[((uint)&((CACHE*)0)->indices==8)?1:-1];
typedef char layout_VE_delta[((uint)&((VE*)0)->delta==0)?1:-1];
typedef char layout_VE_fn[((uint)&((VE*)0)->fn==4)?1:-1];
typedef char layout_MATERIAL_vt[((uint)&((MATERIAL*)0)->vt==12)?1:-1];
typedef char layout_MATERIAL_flags[((uint)&((MATERIAL*)0)->flags==32)?1:-1];
typedef char layout_MATERIAL_words[((uint)&((MATERIAL*)0)->words==68)?1:-1];
typedef char layout_MATERIAL_copy[((uint)&((MATERIAL*)0)->copy==72)?1:-1];
typedef char layout_OBJECT_kind[((uint)&((OBJECT*)0)->kind==4)?1:-1];
typedef char layout_OBJECT_subtype[((uint)&((OBJECT*)0)->subtype==5)?1:-1];
typedef char layout_OBJECT_tint[((uint)&((OBJECT*)0)->tint==8)?1:-1];
typedef char layout_OBJECT_textureScale[((uint)&((OBJECT*)0)->textureScale==20)?1:-1];
typedef char layout_OBJECT_segmentCount[((uint)&((OBJECT*)0)->segmentCount==28)?1:-1];
typedef char layout_OBJECT_segments[((uint)&((OBJECT*)0)->segments==32)?1:-1];
typedef char layout_OBJECT_property[((uint)&((OBJECT*)0)->property==36)?1:-1];
typedef char layout_OBJECT_override[((uint)&((OBJECT*)0)->override==40)?1:-1];
typedef char layout_D_kind[((uint)&((D*)0)->kind==0)?1:-1];
typedef char layout_D_count[((uint)&((D*)0)->count==1)?1:-1];
typedef char layout_D_flags[((uint)&((D*)0)->flags==2)?1:-1];
typedef char layout_D_pad3[((uint)&((D*)0)->pad3==3)?1:-1];
typedef char layout_D_radius[((uint)&((D*)0)->radius==4)?1:-1];
typedef char layout_D_chain[((uint)&((D*)0)->chain==8)?1:-1];
typedef char layout_D_base[((uint)&((D*)0)->base==12)?1:-1];
typedef char layout_D_words[((uint)&((D*)0)->words==16)?1:-1];
typedef char layout_TRANSFORM_world[((uint)&((TRANSFORM*)0)->world==64)?1:-1];
typedef char layout_BONE_value[((uint)&((BONE*)0)->value==0)?1:-1];
typedef char layout_BONE_index[((uint)&((BONE*)0)->index==8)?1:-1];
typedef char layout_BONE_transform[((uint)&((BONE*)0)->transform==12)?1:-1];
typedef char layout_BONE_local[((uint)&((BONE*)0)->local==16)?1:-1];
typedef char layout_E_unknown[((uint)&((E*)0)->unknown==0)?1:-1];
typedef char layout_E_transform[((uint)&((E*)0)->transform==4)?1:-1];
typedef char layout_E_parent[((uint)&((E*)0)->parent==8)?1:-1];
typedef char layout_E_flags[((uint)&((E*)0)->flags==12)?1:-1];
typedef char layout_E_chain[((uint)&((E*)0)->chain==16)?1:-1];
typedef char layout_E_base[((uint)&((E*)0)->base==20)?1:-1];
typedef char layout_E_bones[((uint)&((E*)0)->bones==24)?1:-1];
typedef char layout_E_skin[((uint)&((E*)0)->skin==28)?1:-1];
typedef char layout_E_override[((uint)&((E*)0)->override==32)?1:-1];
typedef char layout_E_sphere[((uint)&((E*)0)->sphere==36)?1:-1];
typedef char layout_LIST_first[((uint)&((LIST*)0)->first==0)?1:-1];
typedef char layout_LIST_last[((uint)&((LIST*)0)->last==4)?1:-1];
typedef char layout_LIST_stride[((uint)&((LIST*)0)->stride==8)?1:-1];
typedef char layout_SKIN_owner[((uint)&((SKIN*)0)->owner==0)?1:-1];
typedef char layout_SKIN_entry[((uint)&((SKIN*)0)->entry==4)?1:-1];
typedef char layout_SKIN_tag[((uint)&((SKIN*)0)->tag==8)?1:-1];
typedef char layout_SKIN_context[((uint)&((SKIN*)0)->context==12)?1:-1];
typedef char layout_SKIN_count[((uint)&((SKIN*)0)->count==16)?1:-1];
typedef char layout_SKIN_first[((uint)&((SKIN*)0)->first==20)?1:-1];
typedef char layout_SKIN_second[((uint)&((SKIN*)0)->second==24)?1:-1];
typedef char layout_SKIN_flags[((uint)&((SKIN*)0)->flags==28)?1:-1];
typedef char layout_SKIN_base[((uint)&((SKIN*)0)->base==32)?1:-1];
typedef char layout_SKIN_kind[((uint)&((SKIN*)0)->kind==48)?1:-1];
typedef char layout_SKIN_coefficient[((uint)&((SKIN*)0)->coefficient==52)?1:-1];
typedef char layout_SKIN_frame[((uint)&((SKIN*)0)->frame==80)?1:-1];
typedef char layout_SKIN_rows[((uint)&((SKIN*)0)->rows==144)?1:-1];
typedef char layout_SKIN_next[((uint)&((SKIN*)0)->next==156)?1:-1];
typedef char layout_SKINROW_count[((uint)&((SKINROW*)0)->count==0)?1:-1];
typedef char layout_SKINROW_positions[((uint)&((SKINROW*)0)->positions==4)?1:-1];
typedef char layout_SKINROW_outputs[((uint)&((SKINROW*)0)->outputs==8)?1:-1];
typedef char layout_SKINROW_next[((uint)&((SKINROW*)0)->next==24)?1:-1];
typedef char layout_REC_count[((uint)&((REC*)0)->count==0)?1:-1];
typedef char layout_REC_flags[((uint)&((REC*)0)->flags==4)?1:-1];
typedef char layout_REC_uv[((uint)&((REC*)0)->uv==8)?1:-1];
typedef char layout_REC_positions[((uint)&((REC*)0)->positions==12)?1:-1];
typedef char layout_REC_packed[((uint)&((REC*)0)->packed==16)?1:-1];
typedef char layout_REC_rgba[((uint)&((REC*)0)->rgba==20)?1:-1];
typedef char layout_REC_normal[((uint)&((REC*)0)->normal==24)?1:-1];
typedef char layout_REC_zero[((uint)&((REC*)0)->zero==28)?1:-1];
typedef char layout_RECHEAD_descriptor[((uint)&((RECHEAD*)0)->descriptor==0)?1:-1];
typedef char layout_RECHEAD_total[((uint)&((RECHEAD*)0)->total==4)?1:-1];
typedef char layout_RECHEAD_records[((uint)&((RECHEAD*)0)->records==8)?1:-1];
typedef char layout_RECHEAD_next[((uint)&((RECHEAD*)0)->next==12)?1:-1];
typedef char layout_OWNER_owner[((uint)&((OWNER*)0)->owner==0)?1:-1];
typedef char layout_OWNER_objectCount[((uint)&((OWNER*)0)->objectCount==36)?1:-1];
typedef char layout_OWNER_objects[((uint)&((OWNER*)0)->objects==40)?1:-1];
typedef char layout_OWNER_extraCount[((uint)&((OWNER*)0)->extraCount==44)?1:-1];
typedef char layout_OWNER_ownerIDs[((uint)&((OWNER*)0)->ownerIDs==48)?1:-1];
typedef char layout_OWNER_stamp[((uint)&((OWNER*)0)->stamp==76)?1:-1];
typedef char layout_OWNER_flags[((uint)&((OWNER*)0)->flags==80)?1:-1];
typedef char layout_OWNER_skin[((uint)&((OWNER*)0)->skin==88)?1:-1];
typedef char layout_OWNER_saved[((uint)&((OWNER*)0)->saved==92)?1:-1];
typedef char layout_PARAM_value[((uint)&((PARAM*)0)->value==0)?1:-1];
typedef char layout_PARAM_words[((uint)&((PARAM*)0)->words==4)?1:-1];
typedef char layout_PARAM_kind[((uint)&((PARAM*)0)->kind==8)?1:-1];
typedef char layout_FACE_count[((uint)&((FACE*)0)->count==0)?1:-1];
typedef char layout_FACE_object[((uint)&((FACE*)0)->object==4)?1:-1];
typedef char layout_FACE_flags[((uint)&((FACE*)0)->flags==8)?1:-1];
typedef char layout_FACE_override[((uint)&((FACE*)0)->override==12)?1:-1];
typedef char layout_FACE_unique[((uint)&((FACE*)0)->unique==16)?1:-1];
typedef char layout_FACE_indices[((uint)&((FACE*)0)->indices==20)?1:-1];
typedef char layout_FACE_positions[((uint)&((FACE*)0)->positions==24)?1:-1];
typedef char layout_FACE_uv[((uint)&((FACE*)0)->uv==28)?1:-1];
typedef char layout_FACE_packed[((uint)&((FACE*)0)->packed==32)?1:-1];
typedef char layout_FACE_colors[((uint)&((FACE*)0)->colors==36)?1:-1];
typedef char layout_FACE_secondColors[((uint)&((FACE*)0)->secondColors==40)?1:-1];
typedef char layout_FACE_alpha[((uint)&((FACE*)0)->alpha==44)?1:-1];
typedef char layout_FACE_extra[((uint)&((FACE*)0)->extra==48)?1:-1];
typedef char layout_FACE_rgba[((uint)&((FACE*)0)->rgba==52)?1:-1];
typedef char layout_FACE_normal[((uint)&((FACE*)0)->normal==56)?1:-1];
typedef char layout_FACE_weights[((uint)&((FACE*)0)->weights==60)?1:-1];
typedef char layout_REMAP_vertex[((uint)&((REMAP*)0)->vertex==0)?1:-1];
typedef char layout_REMAP_destination[((uint)&((REMAP*)0)->destination==4)?1:-1];
typedef char layout_REMAP_destinationIndex[((uint)&((REMAP*)0)->destinationIndex==8)?1:-1];
typedef char layout_REMAP_source[((uint)&((REMAP*)0)->source==12)?1:-1];
typedef char layout_REMAP_sourceIndex[((uint)&((REMAP*)0)->sourceIndex==16)?1:-1];
typedef char layout_ROW_position[((uint)&((ROW*)0)->position==0)?1:-1];
typedef char layout_ROW_normSplit[((uint)&((ROW*)0)->normSplit==2)?1:-1];
typedef char layout_ROW_end[((uint)&((ROW*)0)->end==4)?1:-1];
typedef char layout_ROW_countFlags[((uint)&((ROW*)0)->countFlags==6)?1:-1];
typedef char layout_ROW_segments[((uint)&((ROW*)0)->segments==8)?1:-1];
typedef char layout_ROW_extra[((uint)&((ROW*)0)->extra==14)?1:-1];
typedef char layout_ROW_reordered[((uint)&((ROW*)0)->reordered==16)?1:-1];
typedef char layout_ROW_remap[((uint)&((ROW*)0)->remap==18)?1:-1];
typedef char layout_ROW_override[((uint)&((ROW*)0)->override==20)?1:-1];
typedef char layout_ROW_pad16[((uint)&((ROW*)0)->pad16==22)?1:-1];
typedef char layout_ROW_textureScale[((uint)&((ROW*)0)->textureScale==24)?1:-1];
typedef char layout_ROW_uvAux[((uint)&((ROW*)0)->uvAux==26)?1:-1];
typedef char layout_ROW_weights[((uint)&((ROW*)0)->weights==28)?1:-1];
typedef char layout_ROW_property[((uint)&((ROW*)0)->property==30)?1:-1];
typedef char layout_HEADER_unknown[((uint)&((HEADER*)0)->unknown==0)?1:-1];
typedef char layout_HEADER_entry[((uint)&((HEADER*)0)->entry==2)?1:-1];
typedef char layout_HEADER_extra[((uint)&((HEADER*)0)->extra==4)?1:-1];
typedef char layout_HEADER_special[((uint)&((HEADER*)0)->special==6)?1:-1];
typedef char layout_HEADER_flags[((uint)&((HEADER*)0)->flags==8)?1:-1];
typedef char layout_HEADER_base[((uint)&((HEADER*)0)->base==10)?1:-1];
typedef char layout_HEADER_skinFlags[((uint)&((HEADER*)0)->skinFlags==12)?1:-1];
typedef char layout_HEADER_skinBase[((uint)&((HEADER*)0)->skinBase==14)?1:-1];
typedef char layout_HEADER_bones[((uint)&((HEADER*)0)->bones==16)?1:-1];
typedef char layout_HEADER_rows[((uint)&((HEADER*)0)->rows==24)?1:-1];
typedef char layout_CURVE_position[((uint)&((CURVE*)0)->position==0)?1:-1];
typedef char layout_CURVE_unknownC[((uint)&((CURVE*)0)->unknownC==12)?1:-1];
typedef char layout_CURVE_slope[((uint)&((CURVE*)0)->slope==16)?1:-1];
typedef char layout_CURVE_kind[((uint)&((CURVE*)0)->kind==24)?1:-1];
typedef char layout_CURVE_direct[((uint)&((CURVE*)0)->direct==28)?1:-1];
typedef char layout_CURVE_offset[((uint)&((CURVE*)0)->offset==32)?1:-1];
typedef char layout_CURVE_unknown2C[((uint)&((CURVE*)0)->unknown2C==44)?1:-1];
typedef char layout_JOB_positions[((uint)&((JOB*)0)->positions==0)?1:-1];
typedef char layout_JOB_rgba[((uint)&((JOB*)0)->rgba==4)?1:-1];
typedef char layout_JOB_normals[((uint)&((JOB*)0)->normals==8)?1:-1];
typedef char layout_JOB_alpha[((uint)&((JOB*)0)->alpha==12)?1:-1];
typedef char layout_JOB_extra[((uint)&((JOB*)0)->extra==16)?1:-1];
typedef char layout_JOB_colors[((uint)&((JOB*)0)->colors==20)?1:-1];
typedef char layout_JOB_secondColors[((uint)&((JOB*)0)->secondColors==24)?1:-1];
typedef char layout_JOB_scale[((uint)&((JOB*)0)->scale==28)?1:-1];
typedef char layout_JOB_outAlpha[((uint)&((JOB*)0)->outAlpha==32)?1:-1];
typedef char layout_JOB_outExtra[((uint)&((JOB*)0)->outExtra==36)?1:-1];
typedef char layout_INPUT_count[((uint)&((INPUT*)0)->count==0)?1:-1];
typedef char layout_INPUT_material[((uint)&((INPUT*)0)->material==4)?1:-1];
typedef char layout_INPUT_flags[((uint)&((INPUT*)0)->flags==8)?1:-1];
typedef char layout_PACKET_params[((uint)&((PACKET*)0)->params==0)?1:-1];
typedef char layout_PACKET_input[((uint)&((PACKET*)0)->input==0)?1:-1];
typedef char layout_PACKET_color[((uint)&((PACKET*)0)->color==0)?1:-1];
typedef char layout_REQUEST_bytes[((uint)&((REQUEST*)0)->bytes==0)?1:-1];
typedef char layout_REQUEST_alignment[((uint)&((REQUEST*)0)->alignment==4)?1:-1];
typedef char layout_TEMP_skin[((uint)&((TEMP*)0)->skin==0)?1:-1];
typedef char layout_TEMP_builder[((uint)&((TEMP*)0)->builder==0)?1:-1];
typedef char layout_DMAS_m_pbMax[((uint)&((DMAS*)0)->m_pbMax==0)?1:-1];
typedef char layout_DMAS_m_ab[((uint)&((DMAS*)0)->m_ab==4)?1:-1];
typedef char layout_DMAS_m_pqwCnt[((uint)&((DMAS*)0)->m_pqwCnt==8)?1:-1];
typedef char layout_DMAS_m_pb[((uint)&((DMAS*)0)->m_pb==12)?1:-1];
typedef char layout_DMAS_m_fPad[((uint)&((DMAS*)0)->m_fPad==16)?1:-1];
typedef char layout_DMAS_m_fEndPrim[((uint)&((DMAS*)0)->m_fEndPrim==20)?1:-1];
typedef char layout_VIFS_m_unMask[((uint)&((VIFS*)0)->m_unMask==28)?1:-1];
typedef char layout_VIFS_m_fCheckCnt[((uint)&((VIFS*)0)->m_fCheckCnt==32)?1:-1];
