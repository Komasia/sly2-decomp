/* __get_eh_context (0x23E398; gcc 2.95 libgcc2.c): the current exception context through the function pointer
 * get_eh_context (D_002C60BC; eh_context_initialize at first). */
// name: libgcc (gcc 2.95 libgcc2.c __get_eh_context: return (*get_eh_context)(); src/lib names D_002C60BC get_eh_context)
extern void *(*D_002C60BC)(void);   /* get_eh_context */

void *__get_eh_context(void)
{
    return D_002C60BC();
}
