/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "raylib.h"
#include <iostream>
#include <string>

namespace zappy {
    class Text {
    public:
        Text() = default;
        ~Text();

        Font getDefaultFont();
        void loadFont(const std::string& path);
        void loadFontFromImage(Image image, Color key, int firstChar);
        void loadFontEx(const std::string& path, int fontSize, int* fontChars, int glyphCount);

        void drawText(const char *text, int posX, int posY, int fontSize, Color color);
        void drawText(const char *text, Vector2 position, float fontSize, float spacing, Color tint);

    private:
        Font _font;
    };
}

#endif /* !TEXT_HPP_ */
