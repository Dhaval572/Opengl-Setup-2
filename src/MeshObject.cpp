#include <MeshObject.h>
#include <numeric> // for std::accumulate

MeshObject::MeshObject() = default;

MeshObject::MeshObject
(
    const GLfloat* vertices, 
    uint32_t vertex_count, 
    const GLuint* layout, 
    uint32_t layout_count
)
{
    SetupMesh(vertices, vertex_count, layout, layout_count);
}

MeshObject::MeshObject
(
    const GLfloat* vertices, 
    uint32_t vertex_count,
    const GLuint* layout, 
    uint32_t layout_count,
    const GLuint* indices, 
    uint32_t index_count_in
)
{
    b_HasEbo = true;
    index_count = static_cast<GLsizei>(index_count_in);
    SetupMesh
    (
        vertices, 
        vertex_count, 
        layout, 
        layout_count, 
        indices, 
        index_count_in
    );
}

MeshObject::~MeshObject()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    if (b_HasEbo)
    {
        glDeleteBuffers(1, &ebo);
    }
}

void MeshObject::Bind() const
{
    glBindVertexArray(vao);
}

void MeshObject::Unbind() const
{
    glBindVertexArray(0);
}

void MeshObject::Draw() const
{
    Bind();
    if (b_HasEbo)
    {
        glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, index_count);
    }
    Unbind();
}

void MeshObject::SetupMesh
(
    const GLfloat* vertices, 
    uint32_t vertex_count, 
    const GLuint* layout, 
    uint32_t layout_count
)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    Bind();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData
    (
        GL_ARRAY_BUFFER, 
        vertex_count * sizeof(GLfloat), 
        vertices, 
        GL_STATIC_DRAW
    );

    SetupVertexAttributes(layout, layout_count);

    Unbind();

    uint32_t stride = 0;
    for (uint32_t i = 0; i < layout_count; ++i)
    {
        stride += layout[i];
    }
    index_count = static_cast<GLsizei>(vertex_count / stride);
}

void MeshObject::SetupMesh
(
    const GLfloat* vertices, 
    uint32_t vertex_count,
    const GLuint* layout, 
    uint32_t layout_count,
    const GLuint* indices, 
    uint32_t index_count_in
)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    Bind();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData
    (
        GL_ARRAY_BUFFER, 
        vertex_count * sizeof(GLfloat), 
        vertices, 
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData
    (
        GL_ELEMENT_ARRAY_BUFFER, 
        index_count_in * sizeof(GLuint), 
        indices, 
        GL_STATIC_DRAW
    );
    SetupVertexAttributes(layout, layout_count);
    Unbind();
}

void MeshObject::SetupVertexAttributes
(
    const GLuint* layout, 
    uint32_t layout_count
)
{
    GLuint stride = 0;
    for (uint32_t i = 0; i < layout_count; ++i)
    {
        stride += layout[i];
    }

    GLuint offset = 0;
    for (GLuint i = 0; i < layout_count; ++i)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer
        (
            i, 
            layout[i], 
            GL_FLOAT, 
            GL_FALSE, 
            stride * sizeof(float), 
            reinterpret_cast<void*>(offset * sizeof(float))
        );
        offset += layout[i];
    }
}