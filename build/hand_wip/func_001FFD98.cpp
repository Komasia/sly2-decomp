typedef int qword __attribute__((mode(TI)));
struct CRef;
struct OBJECT;
struct FUNCTION {int references,flags;OBJECT *owner;void *callback,*data;};
struct HOLDER;
struct POOL;
union U {qword q;int i[4];float f[4];};
struct M3 {U rows[3];};
struct TWO {int a,b;};
struct THREE {int a,b,c;};
extern POOL D_00452170;
extern "C" {
FUNCTION *func_00259C18(void);
void func_00259CF8(HOLDER *,FUNCTION *);
void func_00256120(FUNCTION *);
void func_0011CD98(POOL *,void *);
CRef *func_001291A8(CRef *,const CRef *);
CRef *func_00129658(CRef *,const CRef *);
void func_00129EC8(CRef *);
void func_0012A0B0(CRef *,int);
CRef *func_00129518(CRef *,int);
CRef *func_00129558(CRef *,float);
CRef *func_00129598(CRef *,int);
CRef *func_001296A8(CRef *,const qword *);
CRef *func_00129718(CRef *,qword);
CRef *func_00129808(CRef *,const qword *);
CRef *func_00129878(CRef *,const TWO *);
CRef *func_001298F0(CRef *,const THREE *);
CRef *func_00129A10(CRef *,OBJECT *);
CRef *func_00129A70(CRef *,FUNCTION *);
}
union TAG {int integer;float scalar;void *pointer;};
struct CRef {
    int type;TAG tag;
    CRef(){type=-1;}
    CRef(const CRef &r){func_001291A8(this,&r);}
    CRef &operator=(const CRef &r){func_00129658(this,&r);return *this;}
    ~CRef(){func_00129EC8(this);}
    void Reset(int type){func_00129EC8(this);func_0012A0B0(this,type);}
    CRef &Integer(int v){return *func_00129518(this,v);}
    CRef &Scalar(float v){return *func_00129558(this,v);}
    CRef &Boolean(int v){return *func_00129598(this,v);}
    void Vector(const qword *v){func_001296A8(this,v);}
    void Vector(qword v){func_00129718(this,v);}
    void Vector4(const qword *v){func_00129808(this,v);}
    void Pair(const TWO *v){func_00129878(this,v);}
    void Triple(const THREE *v){func_001298F0(this,v);}
    void Object(OBJECT *v){func_00129A10(this,v);}
    void Function(FUNCTION *v){func_00129A70(this,v);}
};
struct HOLDER {
    FUNCTION *function;
    HOLDER(FUNCTION *f){func_00259CF8(this,f);}
    ~HOLDER(){FUNCTION *f=function;if(f&&!--f->references){func_00256120(f);func_0011CD98(&D_00452170,f);}}
};
struct OBJECT {virtual ~OBJECT();};
union GETTER {
    int offset;
    int (OBJECT::*integer)();
    float (OBJECT::*scalar)();
    int (OBJECT::*boolean)();
    qword (OBJECT::*vector)();
    const M3 &(OBJECT::*matrix)();
    void (OBJECT::*vector4)(qword *);
    void (OBJECT::*pair)(TWO *);
    void (OBJECT::*triple)(THREE *);
    CRef (OBJECT::*reference)();
    OBJECT *(OBJECT::*object)();
};
union SETTER {void *function;void (OBJECT::*method)(int);};
struct PROPERTY {int type,flags;GETTER get;SETTER set;void *data;int unused1C;OBJECT *(OBJECT::*resolve)(int);};
static inline void CopyMatrix(M3 *to,const M3 *from){to->rows[0]=from->rows[0];to->rows[1]=from->rows[1];to->rows[2]=from->rows[2];to->rows[0].i[3]=0;to->rows[2].i[3]=0;to->rows[1].i[3]=0;}
static inline void ReadOffset(CRef *result,int type,void *value){
        switch(type){
        case 5:case 6:case 7:case 8:case 14:case 15:case 16:case 17:case 19:case 20:case 23:
            result->Integer(*(int *)value);break;
        case 1:result->Scalar(*(float *)value);break;
        case 0:result->Boolean(*(int *)value!=0);break;
        case 2:result->Vector((qword *)value);break;
        case 4:result->Reset(0x1B);CopyMatrix((M3 *)result->tag.pointer,(M3 *)value);break;
        case 9:result->Vector4((qword *)value);break;
        case 10:result->Pair((TWO *)value);break;
        case 11:result->Triple((THREE *)value);break;
        case 13:break;
        default:
            if(type&0x1000)result->Integer(*(int *)value);
            else if(type&0x2000)result->Object(*(OBJECT **)value);
            break;
        }
}
extern "C" CRef func_001FFD98(OBJECT *object,PROPERTY *property)
{
    CRef result;
    if(property->flags&1){
        HOLDER function(func_00259C18());
        function.function->owner=object;
        function.function->callback=property->set.function;
        function.function->data=property->data;
        result.Function(function.function);
    }else if(property->flags&2){
        if(property->flags&0x2000)object=(object->*property->resolve)(1);
        int type=property->type;
        void *value=(char *)object+property->get.offset;
        ReadOffset(&result,type,value);
    }else{
        if(property->flags&0x2000)object=(object->*property->resolve)(1);
        switch(property->type){
        case 5:case 6:case 7:case 8:case 13:case 14:case 15:case 16:case 17:case 19:case 20:case 23:
            result.Integer((object->*property->get.integer)());break;
        case 1:result.Scalar((object->*property->get.scalar)());break;
        case 0:result.Boolean((object->*property->get.boolean)()!=0);break;
        case 2:result.Vector((object->*property->get.vector)());break;
        case 4:{result.Reset(0x1B);M3 *matrix=(M3 *)result.tag.pointer;const M3 &source=(object->*property->get.matrix)();CopyMatrix(matrix,&source);break;}
        case 9:result.Reset(0x1C);(object->*property->get.vector4)((qword *)result.tag.pointer);break;
        case 10:result.Reset(0x1C);(object->*property->get.pair)((TWO *)result.tag.pointer);break;
        case 11:result.Reset(0x1E);(object->*property->get.triple)((THREE *)result.tag.pointer);break;
        default:
            if(property->type&0x8000)result=(object->*property->get.reference)();
            else if(property->type&0x1000)result.Integer((object->*property->get.integer)());
            else if(property->type&0x2000)result.Object((object->*property->get.object)());
            break;
        }
    }
    return result;
}
