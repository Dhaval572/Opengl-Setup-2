#pragma once
#include <cstdint>
#include <glad/glad.h>

class MeshObject
{
public:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;
    GLsizei index_count = 0;
    bool b_HasEbo = false;

    MeshObject();
    MeshObject
    (
        const GLfloat* vertices, 
        uint32_t vertex_count, 
        const GLuint* layout, 
        uint32_t layout_count
    );

    MeshObject
    (
        const GLfloat* vertices, 
        uint32_t vertex_count,
        const GLuint* layout, 
        uint32_t layout_count,
        const GLuint* indices, 
        uint32_t index_count_in
    );
    ~MeshObject();

    void Bind() const;
    void Unbind() const;
    void Draw() const;

private:
    void SetupMesh
    (
        const GLfloat* vertices, 
        uint32_t vertex_count, 
        const GLuint* layout, 
        uint32_t layout_count
    );

    void SetupMesh
    (
        const GLfloat* vertices, 
        uint32_t vertex_count,
        const GLuint* layout, 
        uint32_t layout_count,
        const GLuint* indices, 
        uint32_t index_count_in
    );

    void SetupVertexAttributes(const GLuint* layout, uint32_t layout_count);
};