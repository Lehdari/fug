FUG_RESOURCE_INITINFO_INIT(VertexData, VertexDataInitInfo_UVSphere) {
    // Check that keys are correct
    assertJsonValidity("VertexDataInitInfo_UVSphere", json, {"type", "segments", "rings"}, {"segments", "rings"});

    // Parse fields
    initInfo.segments = json["segments"];
    initInfo.rings = json["rings"];
}

FUG_RESOURCE_INIT(VertexData, VertexDataInitInfo_UVSphere) {
    // Check parameters
    if (initInfo.segments < 4) {
        FUG_LOG(LogLevel::Error)("VertexDataInitInfo_UVSphere: expected at least 4 segments\n");
        throw;
    }
    if (initInfo.rings < 2) {
        FUG_LOG(LogLevel::Error)("VertexDataInitInfo_UVSphere: expected at least 2 rings\n");
        throw;
    }

    usingTexCoords_ = true;
    usingNormals_ = true;
    usingIndexing_ = true;

    positions_.clear();
    texCoords_.clear();
    normals_.clear();
    indices_.clear();

    // Generate verts
    for (auto i = 0u; i <= initInfo.segments; i++) {
        float segmentFrac = (float)i / initInfo.segments;
        float theta = 2 * PI * segmentFrac;

        for (auto j = 0u; j <= initInfo.rings; j++) {
            float ringFrac = (float)j / initInfo.rings;
            float phi = PI * ringFrac;

            std::array<float, 4> pos = { cosf(theta) * sinf(phi),
                                         cosf(phi),
                                         sinf(theta) * sinf(phi),
                                         1.f };

            positions_.emplace_back(pos);
            texCoords_.emplace_back(std::array<float,3>{ segmentFrac,
                                                         1.f - ringFrac,
                                                         0.f });
            normals_.emplace_back(std::array<float,3>{ pos[0], pos[1], pos[2] });
        }
    }

    // Generate indices
    auto segmentLength = initInfo.rings + 1;
    for (auto i = 0u; i < initInfo.segments; i++) {
        // Get index of first vert
        auto startIndex = i * segmentLength;

        // Push top triangle to indices
        indices_.emplace_back(startIndex);
        indices_.emplace_back(startIndex + 1);
        indices_.emplace_back(startIndex + 1 + segmentLength);

        // Push quads to indices
        for (auto j = 1u; j < initInfo.rings - 1; j++) {
            auto v1 = startIndex + j;
            auto v2 = v1 + 1;
            auto v4 = v1 + segmentLength;
            auto v3 = v4 + 1;
            indices_.emplace_back(v1);
            indices_.emplace_back(v2);
            indices_.emplace_back(v3);
            indices_.emplace_back(v3);
            indices_.emplace_back(v4);
            indices_.emplace_back(v1);
        }

        // Push bottom triangle to indices
        auto v1 = startIndex + segmentLength - 2;
        indices_.emplace_back(v1);
        indices_.emplace_back(v1 + 1);
        indices_.emplace_back(v1 + segmentLength);
    }
}

FUG_RESOURCE_DESTROY(VertexData, VertexDataInitInfo_UVSphere) {}
