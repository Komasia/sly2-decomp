struct FONT { int pad[3]; int dy; int pad10; float ry; };
struct RT { int pad[3]; struct FONT *pfont; };
int ClineWrap__9CRichTextf(struct RT *p, float dx);
float FUN_0015e1b0(struct RT *p, float dx)
{
    float dy = (float)p->pfont->dy * p->pfont->ry;
    return dy * (float)ClineWrap__9CRichTextf(p, dx);
}
