#include <renderer.hpp>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "util.hpp"

void Renderer::Init()
{
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &spriteVAO);
    glGenBuffers(1, &spriteVBO);

    // bind the VAO first to store the VBO bind buffer calls
    glBindVertexArray(spriteVAO);

	glBindBuffer(GL_ARRAY_BUFFER, spriteVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // can bind VBO after vertexAttribPointer registers data
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // Shaders
	spriteShader.LoadShaderFromFile(RESOURCES_PATH"shaders/sprite.vs", RESOURCES_PATH"shaders/sprite.fs");
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    spriteShader.SetMatrix4("projection", projection);
    // Text Shader
    textShader.LoadShaderFromFile(RESOURCES_PATH"shaders/text.vs", RESOURCES_PATH"shaders/text.fs");
    textShader.SetMatrix4("projection", projection);

    InitTextRendering();
}

void Renderer::InitTextRendering()
{
    glGenVertexArrays(1, &this->textVAO);
    glGenBuffers(1, &this->textVBO);

    glBindVertexArray(this->textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::RenderText(std::string& text, float x, float y, float scale, glm::vec3 color)
{
    this->textShader.Use();
    this->textShader.SetVector3f("textColor", color);
    
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->textVAO);
    
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = characters[*c];

        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,      ypos + h,   0.0f, 1.0f},
            { xpos,      ypos,       0.0f, 0.0f},
            { xpos + w,  ypos,       1.0f, 0.0f},

            { xpos,      ypos + h,   0.0f, 1.0f},
            { xpos + w,  ypos,       1.0f, 0.0f},
            { xpos + w,  ypos + h,   1.0f, 1.0f}

        };
        // render glyph over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, this->textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * scale; // >> just divides by 2^n so, this means ch.advance / 64
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Renderer::Renderer()
{
    
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &spriteVAO);
	glDeleteBuffers(1, &spriteVBO);
    glDeleteVertexArrays(1, &textVAO);
	glDeleteBuffers(1, &textVBO);
}

void Renderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 color)
{
    this->spriteShader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin to center
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate
    model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    this->spriteShader.Use();
    this->spriteShader.SetMatrix4("model", model);
    this->spriteShader.SetVector3f("spriteColor", color);
    
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->spriteVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}