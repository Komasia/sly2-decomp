/* ResetGaitFeet (0x20BD68): both feet's marker segment states cleared. */
#define OFS_GAIT_AFFOOT 0x9C
// name: SafeHouse port (ResetGaitFeet)
void ResetGaitFeet__FP4GAIT(char *pgait) { *(int *)(pgait + OFS_GAIT_AFFOOT + 4) = 0; *(int *)(pgait + OFS_GAIT_AFFOOT) = 0; }
