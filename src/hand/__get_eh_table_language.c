/* __get_eh_table_language (0x23E780; gcc 2.95 libgcc2.c, right after __get_eh_table_version): an exception
 * descriptor's language (lang.language, the short at +0x4). */
// name: libgcc (gcc 2.95 libgcc2.c static short __get_eh_table_language(exception_descriptor *table))
typedef struct exception_lang_info { short language; short version; } exception_lang_info;
typedef struct exception_descriptor {
    /* 0x0 */ void *runtime_id_field;
    /* 0x4 */ exception_lang_info lang;
} exception_descriptor;

short __get_eh_table_language(exception_descriptor *table)
{
    return table->lang.language;
}
