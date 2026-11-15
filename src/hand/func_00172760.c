typedef int qword __attribute__((mode(TI)));
struct NOISE { char pad[0x20]; qword posSource; qword pos; char pad2[0x4]; int plo; char pad3[0xC]; int kind; };
struct JOBINVESTIGATE { char pad[0x10]; int pguard; char pad2[0x30]; struct NOISE *pnoise; };
/* JOBINVESTIGATE::PosNoise: where the noise is: its source's position when the noise (kind 4) comes from this
 * guard, else its position. */
// name: SafeHouse port (JOBINVESTIGATE::PosNoise)
qword PosNoise__14JOBINVESTIGATE(struct JOBINVESTIGATE *pjob) { struct NOISE *pnoise = pjob->pnoise; if (pnoise->kind == 4 && pnoise->plo == pjob->pguard) return pnoise->posSource; return pjob->pnoise->pos; }
