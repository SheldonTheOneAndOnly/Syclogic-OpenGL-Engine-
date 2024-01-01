#include<classes/rendering/UI.h>

UI::UI(Window w) {

}

Text::Text(string fn) {
    font = fn;

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR: Could not initalize FreeType Library" << std::endl;
    }

    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face))
    {
        std::cout << "ERROR: Failed to load font" << std::endl;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR: Failed to load Glyph" << std::endl;
            continue;
        }
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLuint64 charHandle = glGetTextureHandleARB(texture);

        Char character = {
            charHandle,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Chars.insert(std::pair<char, Char>(c, character));

        SetCharBindlessHandle(c, charHandle);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Text::Draw(Shader s, string tx, vec2 pos, int size, vec3 col) {
    glDisable(GL_DEPTH_TEST);
    s.Activate();
    glUniform3f(glGetUniformLocation(s.ID, "textColor"), col.x, col.y, col.z);
    glBindVertexArray(VAO);

    glUniformHandleui64ARB(glGetUniformLocation(s.ID, "char"), handle);

    std::string::const_iterator c;
    for (c = tx.begin(); c != tx.end(); c++)
    {
        Char ch = Chars[*c];

        float xpos = pos.x + ch.Bearing.x * size;
        float ypos = pos.y - (ch.Size.y - ch.Bearing.y) * size;

        float w = ch.Size.x * size;
        float h = ch.Size.y * size;
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        glMakeTextureHandleResidentARB(ch.Handle);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        pos.x += (ch.Advance >> 6) * size;
        glMakeTextureHandleNonResidentARB(ch.Handle);
    }
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
}