/* libmc_rpc.h - memory card library (libmc) RPC protocol as used by src/lib/sceMc*.c.
 * Function numbers follow the SDK's sceMcFunc* constants; the negative return codes are the library's own
 * (returned before any request reaches the IOP). Macros only. */
#ifndef LIBMC_RPC_H
#define LIBMC_RPC_H

#define MC_RPC_ID 0x80000400            /* IOP mcserv */

/* sceMcSync command numbers = RPC function numbers */
#define sceMcFuncNoCardInfo 1
#define sceMcFuncNoOpen     2
#define sceMcFuncNoClose    3
#define sceMcFuncNoSeek     4
#define sceMcFuncNoRead     5
#define sceMcFuncNoWrite    6
#define sceMcFuncNoFlush    10
#define sceMcFuncNoMkdir    11
#define sceMcFuncNoChDir    12
#define sceMcFuncNoGetDir   13
#define sceMcFuncNoFileInfo 14
#define sceMcFuncNoDelete   15
#define sceMcFuncNoFormat   16
#define sceMcFuncNoUnformat 17
#define sceMcFuncNoEntSpace 18

/* library-side errors */
#define MC_ERR_RPC        (-91)         /* sceSifCallRpc failed */
#define MC_ERR_NOT_INIT   (-100)        /* sceMcInit has not bound the server */
#define MC_ERR_BUSY       (-200)        /* another command is still running */
#define MC_ERR_BAD_NAME   (-210)        /* empty file name */

#endif /* LIBMC_RPC_H */
