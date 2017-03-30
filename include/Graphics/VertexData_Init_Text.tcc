FUG_RESOURCE_INITINFO_INIT(VertexData, VertexDataInitInfo_Text) {
    if (json["source"] == "SOURCE_BINARY_OBJ") {
        initInfo.source = VertexDataInitInfo_Text::SOURCE_BINARY_OBJ;
    } else {
        throw;
    }
}

FUG_RESOURCE_INIT(VertexData, VertexDataInitInfo_Text) {
    switch (initInfo.source) {
    case VertexDataInitInfo_Text::SOURCE_BINARY_OBJ:
        {
            if (initResources.size() == 0)
                return; // TODO_EXCEPTION: maybe throw an exception instead?

            positions_.clear();
            texCoords_.clear();
            normals_.clear();
            indices_.clear();

            auto buffer = FUG_RESOURCE_MANAGER.getResource<Text>(initResources[0])->getBufferPtr();
            char lineHeader[32];
            std::vector<std::array<float, 4>> positions;
            std::vector<std::array<float, 3>> texCoords;
            std::vector<std::array<float, 3>> normals;
            std::vector<std::array<unsigned, 9>> indices;

            while(*buffer) {
                if (sscanf(buffer, "%s", lineHeader) == 0)
                    return;

                buffer += strlen(lineHeader)+1;

                if (strcmp(lineHeader, "v") == 0) {
                    std::array<float, 4> position = {0.0f, 0.0f, 0.0f, 1.0f};
                    if (sscanf(buffer, "%f %f %f %f", &position[0], &position[1], &position[2], &position[3]) < 3)
                        throw "VertexData: invalid file!"; // TODO_EXCEPTION
                    positions.push_back(std::move(position));
                }
                else if (strcmp(lineHeader, "vt") == 0) {
                    std::array<float, 3> texCoord = {0.0f, 0.0f, 0.0f};
                    if (sscanf(buffer, "%f %f %f", &texCoord[0], &texCoord[1], &texCoord[2]) < 2)
                        throw "VertexData: invalid file!"; // TODO_EXCEPTION
                    texCoords.push_back(std::move(texCoord));
                }
                else if (strcmp(lineHeader, "vn") == 0) {
                    std::array<float, 3> normal = {0.0f, 0.0f, 0.0f};
                    if (sscanf(buffer, "%f %f %f", &normal[0], &normal[1], &normal[2]) < 3)
                        throw "VertexData: invalid file!"; // TODO_EXCEPTION
                    normals.push_back(std::move(normal));
                }
                else if (strcmp(lineHeader, "f") == 0) {
                    std::array<unsigned, 9> index = {0, 0, 0,  0, 0, 0,  0, 0, 0};
                    if (sscanf(buffer, "%u %u %u", &index[2], &index[1], &index[0]) == 3 ||
                        sscanf(buffer, "%u//%u %u//%u %u//%u", &index[2], &index[8], &index[1], &index[7], &index[1], &index[6]) == 6 ||
                        sscanf(buffer, "%u/%u %u/%u %u/%u", &index[2], &index[5], &index[1], &index[4], &index[0], &index[3]) == 6 ||
                        sscanf(buffer, "%u/%u/%u %u/%u/%u %u/%u/%u", &index[2], &index[5], &index[8], &index[1], &index[4], &index[7], &index[0], &index[3], &index[6]) == 9)
                        indices.push_back(std::move(index));
                    else
                        throw "VertexData: invalid file!"; // TODO_EXCEPTION
                }

                while (*buffer++ != 10)
                    if (*buffer == 0)
                        break;
            }

            std::map<std::array<unsigned, 3>, unsigned> createdVertices;

            usingTexCoords_ = texCoords.size() > 0;
            usingNormals_ = normals.size() > 0;
            usingIndexing_ = true;

            for (auto& indexArray : indices) {
                if (usingTexCoords_ && (indexArray[3] == 0 || indexArray[4] == 0 || indexArray[5] == 0))
                    throw "VertexData: invalid index data (texture coordinates)";

                if (usingNormals_ && (indexArray[6] == 0 || indexArray[7] == 0 || indexArray[8] == 0))
                    throw "VertexData: invalid index data (normals)";

                std::array<unsigned, 3> v1 = { indexArray[0], indexArray[3], indexArray[6] };
                std::array<unsigned, 3> v2 = { indexArray[1], indexArray[4], indexArray[7] };
                std::array<unsigned, 3> v3 = { indexArray[2], indexArray[5], indexArray[8] };

                if (createdVertices[v1] == 0) {
                    positions_.push_back(positions.at(indexArray[0]-1));
                    if (usingTexCoords_)
                        texCoords_.push_back(texCoords.at(indexArray[3]-1));
                    if (usingNormals_)
                        normals_.push_back(normals.at(indexArray[6]-1));

                    createdVertices[v1] = positions_.size()-1;
                }
                indices_.push_back(createdVertices[v1]);

                if (createdVertices[v2] == 0) {
                    positions_.push_back(positions.at(indexArray[1]-1));
                    if (usingTexCoords_)
                        texCoords_.push_back(texCoords.at(indexArray[4]-1));
                    if (usingNormals_)
                        normals_.push_back(normals.at(indexArray[7]-1));

                    createdVertices[v2] = positions_.size()-1;
                }
                indices_.push_back(createdVertices[v2]);

                if (createdVertices[v3] == 0) {
                    positions_.push_back(positions.at(indexArray[2]-1));
                    if (usingTexCoords_)
                        texCoords_.push_back(texCoords.at(indexArray[5]-1));
                    if (usingNormals_)
                        normals_.push_back(normals.at(indexArray[8]-1));

                    createdVertices[v3] = positions_.size()-1;
                }
                indices_.push_back(createdVertices[v3]);
            }
        }
    break;
    }
}

FUG_RESOURCE_DESTROY(VertexData, VertexDataInitInfo_Text) {}
