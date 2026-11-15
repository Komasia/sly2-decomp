/* func_001A3650 (0x1A3650): sets a point light's distance falloff (LIGHT +0x164 sNear / +0x168 sFar, EOPID 155) and
 * rebuilds the light. */
struct FALLOFF { float sNear, sFar; };
struct LIGHT { char pad[0x164]; struct FALLOFF falloff; };
void ComputeLight__FP11LIGHTPARAMS(struct LIGHT *plight);
void func_001A3650(struct LIGHT *plight, struct FALLOFF *pfalloff) { plight->falloff = *pfalloff; ComputeLight__FP11LIGHTPARAMS(plight); }
