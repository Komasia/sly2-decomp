/* func_001A2388 (0x1A2388): the actors' vtable slot 93, the end of a deadly damage reaction (8..12): shuts the eyes
 * (SetAloEyesClosed 1.0), then 0x140EB0 (task event 0x10: the job restarts at its checkpoint). SafeHouse damage.cpp. */
void SetAloEyesClosed__FP3ALOf(void *palo, float g);
void func_00140EB0(void *pactor);
void func_001A2388(void *pactor) { SetAloEyesClosed__FP3ALOf(pactor, 1.0f); func_00140EB0(pactor); }
