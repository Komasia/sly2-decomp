/* __get_eh_table_version (0x23E778; gcc 2.95 libgcc2.c, between __eh_rtime_match and old_find_exception_handler): an
 * exception descriptor's language-info version (lang.version, the short at +0x6). */
// name: libgcc (gcc 2.95 libgcc2.c static short __get_eh_table_version(exception_descriptor *table))
typedef struct exception_lang_info { short language; short version; } exception_lang_info;
typedef struct exception_descriptor {
    /* 0x0 */ void *runtime_id_field;
    /* 0x4 */ exception_lang_info lang;
} exception_descriptor;

short __get_eh_table_version(exception_descriptor *table)
{
    return table->lang.version;
}
