#include "Text.hpp"

namespace zappy {
    Font Text::getDefaultFont() {
        return GetFontDefault();
    }

    void Text::loadFont(const std::string& path) {
        _font = LoadFont(path.c_str());
    }

    void Text::loadFontFromImage(Image image, Color key, int firstChar) {
        _font = LoadFontFromImage(image, key, firstChar);
    }

    void Text::loadFontEx(const std::string& path, int fontSize, int* fontChars = NULL, int glyphCount = 0) {
        _font = LoadFontEx(path.c_str(), fontSize, fontChars, glyphCount);
    }

    void Text::drawText(const char *text, int posX, int posY, int fontSize, Color color) {
        DrawText(text, posX, posY, fontSize, color);
    }

    void Text::drawText(const char *text, Vector2 position, float fontSize, float spacing, Color tint) {
        DrawTextEx(_font, text, position, fontSize, spacing, tint);
    }

    Text::~Text() {
        // UnloadFont(_font);
    }
}