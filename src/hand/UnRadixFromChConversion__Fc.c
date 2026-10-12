int UnRadixFromChConversion__Fc(unsigned char ch)
{
    switch (ch) {
    case 'd':
    case 'i':
    case 'u':
        return 10;
    case 'B':
    case 'b':
        return 2;
    case 'o':
        return 8;
    case 'x':
        return 16;
    default:
        return 10;
    }
}
