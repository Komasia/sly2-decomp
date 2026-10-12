struct RPL { int a; float z; int pad[2]; };
int NCmpPrplReverseZ(RPL **pprpl1, RPL **pprpl2)
{
    RPL *plhs = *pprpl1;
    RPL *prhs = *pprpl2;
    if (prhs->z < plhs->z)
        return -1;
    if (plhs->z < prhs->z)
        return 1;
    return plhs - prhs;
}
