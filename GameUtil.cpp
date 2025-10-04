#include <DxLib.h>

void drawTextC(int x, int y, const char* txt, int size, unsigned int text_color, unsigned int edge_color) {
    ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
    SetFontSize(size);
    int strWidth = GetDrawStringWidth(txt, strlen(txt));
    x -= strWidth / 2;
    y -= size / 2;
    DrawString(x, y, txt, text_color, edge_color);
}

//‰æ‘œ‚ğ’†S‚É•`‚­
void drawImage(int img, int x, int y) {
    int w, h;
    GetGraphSize(img, &w, &h);
    DrawGraph(x - w / 2, y - h / 2, img, true);
}