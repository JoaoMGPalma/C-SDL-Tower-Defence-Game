#include "DrawText.h"
//*****************************************************************************//
// FUNÇÃO DE RENDERIZAÇÃO DE TEXTO. DESENHA CARACTERES NO ECRÃ UTILIZANDO UMA   //
// MATRIZ BITMAP 5x7, SUPORTANDO ESCALONAMENTO E CORES PERSONALIZADAS.         //
//*****************************************************************************//
void drawText(SDLWindow &win, const std::string &text, int x, int y, int scale, SDLColor color)
{
    win.setColor(color);

    int cursorX = x; // Posição X atual
    int cursorY = y; // Posição Y atual

    for (char c : text)
    {
        // Trata espaços avançando o cursor
        if (c == ' ') {
            cursorX += 6 * scale;
            continue;
        }

        // Converte minúsculas para maiúsculas
        if (c >= 'a' && c <= 'z')
            c -= 32;

        int index = -1;

        // Mapeia letras (0-25) e números (26-35)
        if (c >= 'A' && c <= 'Z')
            index = c - 'A';
        else if (c >= '0' && c <= '9')
            index = (c - '0') + 26;

        if (index < 0)
            continue;

        // Desenha a matriz 5x7 do caractere
        for (int row = 0; row < 7; row++)
        {
            uint8_t rowBits = FONT5x7[index][row];
            for (int col = 0; col < 5; col++)
            {
                // Verifica se o bit na posição está ativo
                if (rowBits & (1 << (4 - col)))
                    win.drawFilledRect(cursorX + col * scale,
                                       cursorY + row * scale,
                                       scale,
                                       scale);
            }
        }

        cursorX += 6 * scale; // Avança para o próximo caractere
    }
}
