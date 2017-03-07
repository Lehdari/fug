FUG_RESOURCE_INITINFO_INIT(Mesh, MeshInitInfo_Default) {
}

FUG_RESOURCE_INIT(Mesh, MeshInitInfo_Default) {
    if (initResources.size() < 1 || depResources.size() < 1)
    return;
    
    auto vertexData = FUG_RESOURCE_MANAGER.template getResource<VertexData>(initResources[0]);
    _material = FUG_RESOURCE_MANAGER.template getResource<Material>(depResources[0]);
    
    auto positions = vertexData->getPositions();
    auto texCoords = vertexData->getTextureCoordinates();
    auto normals = vertexData->getNormals();
    auto indices = vertexData->getIndices();
    
    //  create and bind the VAO
    glGenVertexArrays(1, &_vertexArrayObjectId);
    glBindVertexArray(_vertexArrayObjectId);
    
    //  upload the vertex data to GPU and set up the vertex attribute arrays
    glGenBuffers(1, &_positionBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, _positionBufferId);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(std::array<float, 4>), &positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    
    glGenBuffers(1, &_texCoordBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, _texCoordBufferId);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(std::array<float, 3>), &texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    
    glGenBuffers(1, &_normalBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, _normalBufferId);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(std::array<float, 3>), &normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    
    _nIndices = indices.size();
    glGenBuffers(1, &_elementBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _nIndices * sizeof(unsigned), &indices[0], GL_STATIC_DRAW);
    
    //  unbind the VAO so it won't be changed outside this function
    glBindVertexArray(0);
}

FUG_RESOURCE_DESTROY(Mesh, MeshInitInfo_Default) {
    if (_vertexArrayObjectId != 0)
        glDeleteVertexArrays(1, &_vertexArrayObjectId);

    glDeleteBuffers(1, &_positionBufferId);
    glDeleteBuffers(1, &_texCoordBufferId);
    glDeleteBuffers(1, &_normalBufferId);
    glDeleteBuffers(1, &_elementBufferId);
}
