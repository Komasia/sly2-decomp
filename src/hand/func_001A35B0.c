/* func_001A35B0 (0x1A35B0): sets the light's kind (LIGHT +0xE0, EOPID 151: 0 directional, 1 point), with
 * func_001A3B38 before, then rebuilds the light. */
struct LIGHT { char pad[0xE0]; int kind; };
void func_001A3B38(struct LIGHT *plight);
void ComputeLight__FP11LIGHTPARAMS(struct LIGHT *plight);
void func_001A35B0(struct LIGHT *plight, int kind) { func_001A3B38(plight); plight->kind = kind; ComputeLight__FP11LIGHTPARAMS(plight); }
