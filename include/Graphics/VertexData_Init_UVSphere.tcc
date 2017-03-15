FUG_RESOURCE_INITINFO_INIT(VertexData, VertexDataInitInfo_UVSphere) {
    initInfo.segments = json["segments"];
    initInfo.rings = json["rings"];
}

FUG_RESOURCE_INIT(VertexData, VertexDataInitInfo_UVSphere) {
    usingTexCoords_ = true;
    usingNormals_ = true;
    usingIndexing_ = true;

    positions_.clear();
    texCoords_.clear();
    normals_.clear();
    indices_.clear();

    // Push top and bottom vertices
    positions_.push_back({ 0.f, 1.f, 0.f, 1.f });
    texCoords_.push_back({ 0.5f, 0.5f });
    normals_.push_back({ 0.f, 1.f, 0.f });
    positions_.push_back({ 0.f, -1.f, 0.f, 1.f });
    texCoords_.push_back({ 0.5f, 0.5f });
    normals_.push_back({ 0.f, -1.f, 0.f });

    // Generate rest of the verts
    auto vertRings = initInfo.rings - 1;
    for (auto i = 0u; i < initInfo.segments; i++) {
        float theta = 2 * PI * i / initInfo.segments;

        for (auto j = 1u; j < initInfo.rings; j++) {
            float phi = PI * j / initInfo.rings;

            std::array<float, 4> pos = { cosf(theta) * sinf(phi),
                                         cosf(phi),
                                         sinf(theta) * sinf(phi),
                                         1.f };

            positions_.push_back(pos);
            texCoords_.push_back({ 0.5f, 0.5f });
            normals_.push_back({ pos[0], pos[1], pos[2] });
        }
    }

    // Generate triangles for n-1 segments
    for (auto i = 0u; i < initInfo.segments; i++) {
        auto startIndex = i * vertRings + 2;

        // Push top triangle to indices
        indices_.push_back(0);
        indices_.push_back(startIndex);
        indices_.push_back(startIndex + vertRings);

        // Push quads to indices
        for (auto j = 1u; j < initInfo.rings - 1; j++) {
            auto v1 = startIndex + j - 1;
            auto v2 = v1 + 1;
            auto v4 = v1 + vertRings;
            auto v3 = v4 + 1;
            indices_.push_back(v1);
            indices_.push_back(v2);
            indices_.push_back(v3);
            indices_.push_back(v3);
            indices_.push_back(v4);
            indices_.push_back(v1);
        }

        // Push bottom triangle to indices
        auto v1 = startIndex + vertRings - 1;
        indices_.push_back(v1);
        indices_.push_back(1);
        indices_.push_back(v1 + vertRings);
    }

    // Last segment
    auto startIndex = (initInfo.segments - 1) * vertRings + 2;

    // Top
    indices_.push_back(0);
    indices_.push_back(startIndex);
    indices_.push_back(2);

    // Quads
    for (auto j = 1u; j < initInfo.rings - 1; j++) {
        auto v1 = startIndex + j - 1;
        auto v2 = v1 + 1;
        auto v4 = j + 1;
        auto v3 = v4 + 1;
        indices_.push_back(v1);
        indices_.push_back(v2);
        indices_.push_back(v3);
        indices_.push_back(v3);
        indices_.push_back(v4);
        indices_.push_back(v1);
    }

    // Bottom
    auto v1 = startIndex + vertRings - 1;
    indices_.push_back(v1);
    indices_.push_back(1);
    indices_.push_back(vertRings + 1);
}

FUG_RESOURCE_DESTROY(VertexData, VertexDataInitInfo_UVSphere) {}
