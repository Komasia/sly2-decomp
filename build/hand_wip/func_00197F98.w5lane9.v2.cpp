typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U r[3]; };
struct M4 { U r[4]; };
struct VTE { short delta, pad; void *fn; };
struct SPACE;
struct CLIP;
struct INPUT { char pad0[0x18]; float heading; float amount; };
struct PHYSICS { char pad0[0x80]; U gravity; };
struct BODY { char pad0[0x30]; U position; char pad40[0x60]; SPACE *frame; char padA4[4]; float deadline; char padAC[4]; U velocity; U goal; U velocityGoal; };
struct ACTOR {
    char pad0[0xC]; VTE *vt; char pad10[0x48]; BODY *body; char pad5C[0x8C]; PHYSICS *physics; char padEC[0x64]; INPUT *input;
    char pad154[0x3C]; U velocity; char pad1A0[8]; float heading; char pad1AC[4]; M3 local; char pad1E0[0x60]; U offset;
};
struct DATA { char pad0[4]; float amount; };
struct FOCUS { char pad0[0x114]; DATA *data; };
struct SOURCE { char pad0[0xC]; VTE *vt; char pad10[0x148]; float height; char pad15C[0x18]; SOURCE *next; char pad178[4]; int state; };
struct OBJECT { char pad0[0xC]; VTE *vt; char pad10[0xD0]; OBJECT *next; char padE4[4]; float radius; char padEC[0x48]; int state; };
struct TRACK { int id; float weight; float pad; };
struct CONTEXT {
    ACTOR *actor; int state; int variant; void *source; float parameter; float value; float stamp; int mode; float time;
    int jump; int flags28, flags2C, flags30; float gain; float scale; float height; int combo; float tRelease; float tPress;
    float tRelease2; char pad50[0x50]; U desired; float lastHeading; float blend; float speedLimit; char padBC[0xA4];
    OBJECT *velocitySource; float velocityScale; float oldScale; OBJECT *focus; OBJECT *other; int focused; CLIP *scripted;
    float scriptedGain; char pad180[4]; TRACK tracks[4]; char pad1B4[4]; CLIP *multi; FOCUS *scriptFocus; float blend0, blend1;
};
struct SAMPLER { char data[0x20]; virtual void f1(); virtual void f2(); virtual void Sample(ACTOR *, U *, float *, float); };
struct BASE_E0 { char data[0xE0]; };
struct BASE_190 { char data[0x190]; };
struct PATH : BASE_E0, SAMPLER {};
struct SPLINE : BASE_190, SAMPLER {};
struct CLOCK { float t, dt; };
struct LM { float low, high; };
struct SMP { float a, b, c; };
struct VU_FLOAT { qword q; };

extern "C" {
extern CLOCK D_002DDED0;
extern ACTOR *D_002E1E40;
extern SOURCE *D_003E13E4;
extern OBJECT *D_003E1420;
extern qword D_002A2DD0, D_002A2DC0, D_002A2DA0, D_002BF890;
extern float D_002BF780[];
extern float D_002BF730, D_002BF734, D_002BF834, D_002BF838, D_002BF83C, D_002BF840, D_002BF844, D_002BF848;
extern float D_002BF878, D_002BF87C, D_002BF880, D_002BF8A0;
extern LM D_002BF798, D_002BF850, D_002BF858, D_002BF870;
extern SMP D_002BF860;
qword func_001A62E8(void *);
void func_0019A4A0(CONTEXT *, qword, void *, qword, qword, float *, float *, qword *, qword *);
void func_0011EE08(qword, qword, qword, qword *, float *, float *);
qword func_0022D348(SPACE *, SPACE *, qword);
qword func_0022FC48(SPACE *, SPACE *, qword);
qword func_0022FCC8(SPACE *, SPACE *, qword);
void func_00195FB8(CONTEXT *, int, void *);
void func_002309E8(SPACE *, SPACE *, M4 *, M4 *, float);
void func_00117120(float, float, float, qword, qword, qword, qword, qword *, qword *, qword *);
float func_00204740(ACTOR *);
float func_0011CF60(float);
void func_0011D608(float, float *, float *);
float func_0011D018(float, float, float, SMP *, float *);
void func_001384C0(CLIP *);
void func_001E67B8(void *, float, qword *, qword *);
void func_001CC2E8(void *);
void func_002046B0(ACTOR *, qword);
void func_00204660(ACTOR *, float);
void func_001441E8(ACTOR *, float);
qword func_0011E1A0(float, float, float);
M3 func_0011BA08(qword, qword);
M3 func_0011B500(qword, float);
float func_002458F0(float, float);
float func_00244E10(float);
float func_0011E290(qword, qword, qword *, qword *);
qword func_0011E9F8(qword, float);
void func_00140C88(ACTOR *, void *);
}

static inline qword GetVelocity(void *p) { VTE &v = ((SOURCE *)p)->vt[33]; return ((qword (*)(void *))v.fn)((char *)p + v.delta); }
static inline SPACE *GetFrame(void *p) { VTE &v = ((SOURCE *)p)->vt[32]; return ((SPACE * (*)(void *, void *))v.fn)((char *)p + v.delta, 0); }
static inline int FFacing(ACTOR *p) { VTE &v = p->vt[92]; return ((int (*)(void *))v.fn)((char *)p + v.delta); }

static inline VU_FLOAT VuFloat(float g) { VU_FLOAT v; __asm__("qmtc2.ni %1,%0" : "=j"(v.q) : "r"(g)); return v; }
static inline qword QwSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwAddScaled(qword a, qword b, VU_FLOAT g) { qword r; __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "j"(b), "j"(g.q)); return r; }
static inline qword QwScale(qword a, VU_FLOAT g) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(g.q)); return r; }
static inline float GFromVf(qword v) { float g; __asm__("qmfc2.ni %0,%1" : "=r"(g) : "j"(v)); return g; }
static inline float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static inline float GLengthSqXY(qword v) { qword r; __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(r) : "j"(v)); return GFromVf(r); }
static inline qword QwSqrt(qword v) { qword r; __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(r) : "j"(v)); return r; }
static inline float GLengthXY(qword v) { qword r; __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(r) : "j"(v)); return GFromVf(QwSqrt(r)); }
static inline qword QwDot(qword a, qword b) { qword r, one; __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(r), "=j"(one) : "j"(a), "j"(b)); return r; }
static inline float GLength(qword v) { return GFromVf(QwSqrt(QwDot(v, v))); }
static inline float GMin(float a, float b) { return a < b ? a : b; }
static inline qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
static inline qword Transform(const M4 &m, qword v)
{
    qword q;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(q) : "j"(m.r[0].q), "j"(m.r[1].q), "j"(m.r[2].q), "j"(m.r[3].q), "j"(v));
    return q;
}
static inline qword Rotate(const M3 &m, qword v)
{
    qword q;
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(q) : "j"(m.r[0].q), "j"(m.r[1].q), "j"(m.r[2].q), "j"(v));
    return q;
}
static inline M3 MulM3(const M3 &a, const M3 &b) return r
{
    r.r[0].q = Rotate(a, b.r[0].q);
    r.r[1].q = Rotate(a, b.r[1].q);
    r.r[2].q = Rotate(a, b.r[2].q);
}
static inline qword RotateTranspose(const M3 &m, qword v)
{
    qword q, a, b, c, one;
    __asm__("vmul.xyzw %1,%0,%7\n\tvmaxw.xyzw %4,$vf0,$vf0w\n\tvmul.xyzw %2,%5,%7\n\tvmul.xyzw %3,%6,%7\n\tvadday.x $ACC,%1,%1y\n\tvmaddz.x %0,%4,%1z\n\tvaddax.y $ACC,%2,%2x\n\tvmaddz.y %0,%4,%2z\n\tvaddax.z $ACC,%3,%3x\n\tvmaddy.z %0,%4,%3y"
            : "=j"(q), "=&j"(a), "=&j"(b), "=&j"(c), "=&j"(one) : "j"(m.r[1].q), "j"(m.r[2].q), "j"(v), "0"(m.r[0].q));
    return q;
}
static inline qword QwScaleQ(qword a, qword g) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(g)); return r; }
static inline qword QwCombine(qword a, qword b, VU_FLOAT g0, qword c, VU_FLOAT g1)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddax.xyzw $ACC,%2,%3x\n\tvmaddx.xyzw %0,%4,%5x" : "=j"(r) : "j"(a), "j"(b), "j"(g0.q), "j"(c), "j"(g1.q));
    return r;
}
static inline qword QwDivQ(qword v, qword l) { qword r; __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "j"(l)); return r; }
static inline float GNormalize(U &v)
{
    qword l = QwSqrt(QwDot(v.q, v.q));
    if (GFromVf(l) < 0.0001f)
        v.q = D_002A2DA0;
    else
        v.q = QwDivQ(v.q, l);
    return GFromVf(l);
}
static inline float GLerp(const LM &lm, float u) { return (1.0f - u) * lm.low + u * lm.high; }

extern "C" void func_00197F98(CONTEXT *p)
{
    INPUT *input = p->actor->input;
    switch (p->combo) {
    case 0:
        if (0.9f < input->amount) {
            p->combo = 1;
            p->tPress = D_002DDED0.t;
        } else if (D_002BF834 < D_002DDED0.t - p->tRelease)
            p->jump = 1;
        break;
    case 1:
        if (input->amount < 0.9f) {
            p->combo = 2;
            p->tRelease2 = D_002DDED0.t;
            if (D_002DDED0.t - p->tPress < D_002BF838)
                p->jump = 1;
        }
        break;
    case 3:
        if (0.2f < input->amount)
            p->jump = 1;
        break;
    }

    U pos;
    pos.q = func_001A62E8(p->actor);
    U vel;
    vel.q = GetVelocity(p->actor);
    U point;
    float t, score;

    switch (p->mode) {
    case 0: case 2: case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16:
    case 18: case 19: case 20: case 21: case 22:
        break;
    default: {
        U posBest, velHit, velBest;
        SOURCE *srcBest = 0;
        OBJECT *objBest = 0;
        float scoreBest = 1500.0f;
        float tBest;
        for (SOURCE *src = D_003E13E4; src; src = src->next) {
            if (src->state != 0)
                continue;
            qword posSrc = func_001A62E8(src);
            if (360000.0f < GLengthSqXY(QwSub(posSrc, pos.q)))
                continue;
            if (GetZ(posSrc) + src->height < pos.f[2])
                continue;
            func_0019A4A0(p, vel.q, src, QwSub(posSrc, p->actor->offset.q), D_002A2DD0, &t, &score, &point.q, &velHit.q);
            if (scoreBest < score)
                continue;
            float alpha, dist;
            U delta;
            delta.q = QwSub(pos.q, posSrc);
            qword v = vel.q;
            U rel;
            rel.q = QwSub(v, GetVelocity(src));
            U end;
            end.q = QwAddScaled(delta.q, rel.q, VuFloat(GMin(0.25f, t)));
            delta.f[2] = end.f[2] = 0.0f;
            func_0011EE08(D_002A2DD0, delta.q, end.q, 0, &alpha, &dist);
            if ((D_002BF83C < dist || alpha == 0.0f) && (D_002BF83C * 0.25f < dist || 0.0f < vel.f[2]))
                continue;
            srcBest = src;
            objBest = 0;
            posBest = point;
            velBest = velHit;
            tBest = t;
            scoreBest = score;
        }
        for (OBJECT *obj = D_003E1420; obj; obj = obj->next) {
            U posObj;
            posObj.q = func_001A62E8(obj);
            if (D_002BF840 * D_002BF840 < GLengthSqXY(QwSub(pos.q, posObj.q)))
                continue;
            func_0019A4A0(p, vel.q, obj, QwSub(posObj.q, p->actor->offset.q), D_002A2DD0, &t, &score, &point.q, &velHit.q);
            if (scoreBest < score)
                continue;
            float alpha, dist;
            U velObj;
            velObj.q = func_0022D348(GetFrame(obj), 0, posObj.q);
            U delta;
            delta.q = QwSub(pos.q, posObj.q);
            U rel;
            rel.q = QwSub(vel.q, velObj.q);
            U end;
            end.q = QwAddScaled(delta.q, rel.q, VuFloat(GMin(0.25f, t)));
            delta.f[2] = end.f[2] = 0.0f;

            func_0011EE08(D_002A2DD0, delta.q, end.q, 0, &alpha, &dist);
            if ((obj->radius < dist || alpha == 0.0f) && (obj->radius * 0.25f < dist || 0.0f < vel.f[2]))
                continue;
            objBest = obj;
            srcBest = 0;
            posBest = point;
            velBest = velHit;
            tBest = t;
            scoreBest = score;
        }
        if (srcBest || objBest) {
            BODY *body = p->actor->body;
            body->deadline = D_002DDED0.t + tBest;
            body->goal.q = func_0022FC48(0, body->frame, posBest.q);
            U v;
            v.q = Make(velBest.f[0], velBest.f[1], vel.f[2] + tBest * p->actor->physics->gravity.f[2]);
            body->velocityGoal.q = func_0022FCC8(0, body->frame, v.q);
            if (srcBest)
                func_00195FB8(p, 6, srcBest);
            else
                func_00195FB8(p, 8, objBest);
        }
        break;
    }
    }

    float headingSample = p->actor->heading;
    switch (p->mode) {
    case 6: case 8:
        point.q = QwSub(func_001A62E8(p->source), p->actor->offset.q);
    predict: {
        BODY *body = p->actor->body;
        float dt = body->deadline - D_002DDED0.t;
        SPACE *frame = GetFrame(p->source);
        M4 forecast, derivative;
        func_002309E8(frame, 0, &forecast, &derivative, dt);
        qword local = func_0022FC48(0, frame, point.q);
        body->goal.q = func_0022FC48(0, body->frame, Transform(forecast, local));
        if (p->mode != 10) {
            U v;
            v.q = Transform(derivative, local);
            v.f[2] = vel.f[2] + dt * p->actor->physics->gravity.f[2];
            body->velocityGoal.q = func_0022FCC8(0, body->frame, v.q);
        }
        break;
    }
    case 10: case 11:
        ((SPLINE *)p->source)->Sample(p->actor, &point, &headingSample, p->value);
        goto predict;
    case 9:
        ((PATH *)p->source)->Sample(p->actor, &point, &headingSample, p->value);
        goto predict;
    case 12:
        ((PATH *)p->source)->Sample(p->actor, &point, &headingSample, p->value);
        goto predict;
    case 13:
        ((PATH *)p->source)->Sample(p->actor, &point, &headingSample, p->value);
        goto predict;
    case 18:
        point.q = func_001A62E8(p->source);
        goto predict;
    }

    switch (p->mode) {
    case 6: case 8 ... 16: case 18: {
        BODY *body = p->actor->body;
        float dt = body->deadline - D_002DDED0.t + D_002DDED0.dt;
        U accel0, accel1;
        func_00117120(dt, 0.0f, 1.0f, body->position.q, body->velocity.q, body->goal.q, body->velocityGoal.q, 0, 0, &accel0.q);
        func_00117120(dt, dt, 1.0f, body->position.q, body->velocity.q, body->goal.q, body->velocityGoal.q, 0, 0, &accel1.q);
        if (D_002BF844 < (GLength(accel0.q) + GLength(accel1.q)) * (dt * 0.5f))
            func_00195FB8(p, 4, 0);
        break;
    }
    }

    float offset = D_002BF780[p->variant];
    float heading = p->actor->heading;
    switch (p->mode) {
    case 0:
        if (0.2f < input->amount)
            heading = input->heading + offset;
        break;
    case 11: case 12: case 13:
        heading = headingSample;
        break;
    case 20: {
        float headingOld = func_00204740(p->actor);
        float s, c;
        func_0011D608(func_0011CF60(input->heading - headingOld), &s, &c);
        float lateral = s * input->amount;
        float forward = c * input->amount;
        float mix = (forward + 1.0f) * 0.5f;
        if (p->scriptFocus) {
            DATA *data = p->scriptFocus->data;
            data->amount = func_0011D018(data->amount, GLerp(D_002BF798, mix), D_002DDED0.dt, &D_002BF860, 0);
        }
        p->blend0 = GLerp(D_002BF850, mix);
        float turn = GLerp(D_002BF870, mix) * lateral * D_002DDED0.dt;
        p->blend1 = GLerp(D_002BF858, mix);
        p->scriptedGain = 1.0f - input->amount;
        heading = headingOld + turn;
        if (input->amount != 0.0f) {
            float scale = input->amount / (__builtin_fabsf(lateral) + __builtin_fabsf(forward));
            if (lateral < 0.0f) {
                p->tracks[0].weight = 0.0f;
                p->tracks[1].weight = -lateral * scale;
            } else {
                p->tracks[1].weight = 0.0f;
                p->tracks[0].weight = lateral * scale;
            }
            if (0.0f < forward) {
                p->tracks[3].weight = 0.0f;
                p->tracks[2].weight = forward * scale;
            } else {
                p->tracks[2].weight = 0.0f;
                p->tracks[3].weight = -forward * scale;
            }
        } else {
            p->tracks[0].weight = 0.0f;
            p->tracks[1].weight = 0.0f;
            p->tracks[2].weight = 0.0f;
            p->tracks[3].weight = 0.0f;
        }
        func_001384C0(p->multi);
        break;
    }
    case 14: case 15: {
        U target;
        if (p->mode == 15)
            func_001E67B8(p->source, p->parameter, &target.q, 0);
        else
            target.q = func_001A62E8(p->source);
        if (p->actor != D_002E1E40)
            func_001CC2E8((char *)p->actor + 0x900);
        func_002046B0(p->actor, QwSub(target.q, pos.q));
        heading = p->actor->heading;
        break;
    }
    case 22: {
        func_001441E8(p->actor, D_002BF878);
        p->actor->velocity.q = func_0011E1A0(input->heading + 3.14159265f, input->amount * D_002BF87C, D_002BF880);
        if (D_002BF848 < GLengthXY(vel.q))
            p->actor->heading = func_002458F0(vel.f[1], vel.f[0]) + offset;
        VU_FLOAT half = VuFloat(0.5f);
        VU_FLOAT halfNeg = VuFloat(-0.5f);
        qword up = D_002A2DC0;
        qword a = vel.q;
        qword b = p->actor->velocity.q;
        a = QwSub(a, QwScaleQ(up, QwDot(a, up)));
        b = QwSub(b, QwScaleQ(up, QwDot(b, up)));
        M3 basis = func_0011BA08(D_002A2DC0, QwCombine(D_002BF890, a, half, b, halfNeg));
        ACTOR *actor = p->actor;
        actor->local = MulM3(basis, func_0011B500(D_002A2DC0, actor->heading));
        break;
    }
    case 17: case 19:
        break;
    default:
        if (FFacing(p->actor))
            heading = p->actor->heading;
        else if (D_002BF848 < GLengthXY(vel.q))
            heading = func_002458F0(vel.f[1], vel.f[0]) + offset;
        break;
    }
    if (p->mode != 22)
        func_00204660(p->actor, heading);

    switch (p->mode) {
    case 0 ... 5: case 7: {
        float speed;
        switch (p->mode) {
        case 2: case 3:
            speed = D_002BF734;
            break;
        case 5:
            if (0.2f < input->amount) {
                float g = func_00244E10(input->heading - p->lastHeading);
                if (g < 0.0f)
                    g = 0.0f;
                else if (p->blend < g)
                    g = p->blend;
                p->blend = g;
            }
            if (D_002BF730 < p->speedLimit)
                speed = (1.0f - p->blend) * D_002BF730 + p->blend * p->speedLimit;
            else
                speed = D_002BF730;
            break;
        default:
            speed = D_002BF730;
            break;
        }
        speed *= p->scale;
        U desired;
        desired.q = func_0011E1A0(input->heading, input->amount * speed, 0.0f);
        ACTOR *actor = p->actor;
        actor->velocity.q = QwScale(RotateTranspose(actor->local, desired.q), VuFloat(-1.0f));
        if ((p->mode != 0 || p->combo == 3) && !p->jump) {
            U dir;
            dir.q = GetVelocity(p->actor);
            dir.f[2] = 0.0f;
            float g = GNormalize(dir);
            U perp;
            float proj = func_0011E290(desired.q, dir.q, 0, &perp.q);
            if (proj < g && g * -0.25f < proj) {
                desired.q = QwAddScaled(perp.q, dir.q, VuFloat(g));
                desired.q = func_0011E9F8(desired.q, speed);
            }
        }
        if (p->velocitySource) {
            VU_FLOAT k = VuFloat(p->velocityScale);
            desired.q = QwAddScaled(desired.q, GetVelocity(p->velocitySource), k);
        }
        p->desired = desired;
        if (p->height < pos.f[2])
            p->height = pos.f[2];
        break;
    }
    }
    if (p->focused && p->focus && p->other && p->focus->state == 1 && vel.f[2] < D_002BF8A0)
        func_00140C88(p->actor, p->other);
}
