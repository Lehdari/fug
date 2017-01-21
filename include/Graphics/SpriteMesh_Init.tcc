FUG_RESOURCE_INIT(SpriteMesh, SpriteMeshInitInfo_Default) {
    if (depResources.size() < 1)
        return;

    _material = FUG_RESOURCE_MANAGER.template getResource<SpriteMaterial>(depResources[0]);

    GLfloat positions[]{-1.f, -1.f, 0.f, 1.f,
                        1.f, -1.f, 0.f, 1.f,
                        1.f,  1.f, 0.f, 1.f,
                       -1.f,  1.f, 0.f, 1.f };
    GLuint indices[6] = {0,1,2,2,3,0};

    //  create and bind the VAO
    glGenVertexArrays(1, &_vertexArrayObjectId);
    glBindVertexArray(_vertexArrayObjectId);

    //  upload the vertex data to GPU and set up the vertex attribute arrays
    glGenBuffers(1, &_positionBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, _positionBufferId);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(GLfloat), &positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    _nIndices = 6;
    glGenBuffers(1, &_elementBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _nIndices * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    //  unbind the VAO so it won't be changed outside this function
    glBindVertexArray(0);
}

FUG_RESOURCE_DESTROY(SpriteMesh, SpriteMeshInitInfo_Default) {
    if (_vertexArrayObjectId != 0)
        glDeleteVertexArrays(1, &_vertexArrayObjectId);

    glDeleteBuffers(1, &_positionBufferId);
    glDeleteBuffers(1, &_elementBufferId);
}
