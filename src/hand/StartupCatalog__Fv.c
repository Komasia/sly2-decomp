/* StartupCatalog (0x14B660): the startup table 0x2BFCE0's entry after StartupCd, as in Sly 1's main.c s_asfn
 * (StartupCd, StartupCatalog); the same body as Sly 1's cat.c: the CD state becomes CDS_Ready. */
// name: Sly 1 (StartupCatalog__Fv, cat.c; same startup-table position and body)
enum CDS { CDS_Initing = 0, CDS_Searching = 1, CDS_Waiting = 2, CDS_Ready = 3, CDS_Dead = 4 };
extern int g_cds;

void StartupCatalog__Fv(void)
{
    g_cds = CDS_Ready;
}
