/* func_0020AF28 (0x20AF28, option 362): the guard action's aim records: the aimed reference, its end and the marker. */
struct GUARDACTION { char pad[0x7C]; int oidAimRef, oidAimEndRef, nAimMarker; };
void func_0020AF28(struct GUARDACTION *paction, int oidAimRef, int oidAimEndRef, int nAimMarker) { paction->oidAimRef = oidAimRef; paction->oidAimEndRef = oidAimEndRef; paction->nAimMarker = nAimMarker; }
