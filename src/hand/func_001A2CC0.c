/* func_001A2CC0 (0x1A2CC0): a language's four-character text key "FK$x" (little-endian words), x by language:
 * e english, f french, i italian, g german, s spanish, d dutch, p portuguese, a danish, h finnish, n norwegian,
 * w swedish, j japanese, k korean, c chinese (SafeHouse region.cpp's language order); 0 for others. */
#define LANGKEY(ch) (((ch) << 24) | 0x244B46)  /* 'F' 'K' '$' ch */
int func_001A2CC0(unsigned int nLang)
{
    switch (nLang) {
    case 0: return LANGKEY('e');
    case 1: return LANGKEY('f');
    case 2: return LANGKEY('i');
    case 3: return LANGKEY('g');
    case 4: return LANGKEY('s');
    case 5: return LANGKEY('d');
    case 6: return LANGKEY('p');
    case 7: return LANGKEY('a');
    case 8: return LANGKEY('h');
    case 9: return LANGKEY('n');
    case 10: return LANGKEY('w');
    case 11: return LANGKEY('j');
    case 12: return LANGKEY('k');
    case 13: return LANGKEY('c');
    }
    return 0;
}
