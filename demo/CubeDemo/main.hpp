
using namespace fug;

MeshComponent loadCubeMeshComponent()
{
    // Default ShaderProgram

    auto vert_info_id = FUG_RESOURCE_ID_MAP.getId("vert_info");
    FUG_RESOURCE_MANAGER.addResourceInfo<Text, TextInitInfo_File>
    (vert_info_id, TextInitInfo_File{std::string(FUG_RES_DIRECTORY) + "../res/shader/default_vert.glsl"});

    auto vert_shader_id = FUG_RESOURCE_ID_MAP.getId("vert_shader");
    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderObject, ShaderObjectInitInfo_Text>
    (vert_shader_id, ShaderObjectInitInfo_Text{GL_VERTEX_SHADER}, {vert_info_id}, {});


    auto frag_info_id = FUG_RESOURCE_ID_MAP.getId("frag_info");
    FUG_RESOURCE_MANAGER.addResourceInfo<Text, TextInitInfo_File>
    (frag_info_id, TextInitInfo_File{std::string(FUG_RES_DIRECTORY) + "../res/shader/default_frag.glsl"});

    auto frag_shader_id = FUG_RESOURCE_ID_MAP.getId("frag_shader");
    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderObject, ShaderObjectInitInfo_Text>
    (frag_shader_id, ShaderObjectInitInfo_Text{GL_FRAGMENT_SHADER}, {frag_info_id}, {});


    auto shader_prog_id = FUG_RESOURCE_ID_MAP.getId("shader_program");
    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderProgram, ShaderProgramInitInfo_Default>
    (shader_prog_id, ShaderProgramInitInfo_Default{}, {vert_shader_id, frag_shader_id}, {}, true);

    // Cube Texture

    auto cube_bin_id = FUG_RESOURCE_ID_MAP.getId("cube_binary");
    FUG_RESOURCE_MANAGER.addResourceInfo<Binary, BinaryInitInfo_File>
    (cube_bin_id, BinaryInitInfo_File{"../res/textures/colorkuutio.png"});
    
    auto cube_tex_id = FUG_RESOURCE_ID_MAP.getId("cube_texture");
    FUG_RESOURCE_MANAGER.addResourceInfo<Texture, TextureInitInfo_Binary>
    (cube_tex_id, TextureInitInfo_Binary{TextureInitInfo_Binary::SOURCE_BINARY_PNG,
        GL_CLAMP_TO_BORDER,
        GL_CLAMP_TO_BORDER,
        GL_NEAREST,
        GL_NEAREST},
     {cube_bin_id}, {}, true);

    // Cube Material

    auto cube_mat_id = FUG_RESOURCE_ID_MAP.getId("cube_material");
    FUG_RESOURCE_MANAGER.addResourceInfo<Material, MaterialInitInfo_Default>
    (cube_mat_id, MaterialInitInfo_Default{{"diffuseSampler"},
                                   {"uModelToClip", "uModelToCam", "uNormalToCam"},
                                   {"uSpecularCol"},
                                   {"uSpecularExp"},
                                   Vector3Glf(0.1f, 0.1f, 0.1f), 0.5f},
                                   {}, {shader_prog_id, cube_tex_id}, true);

    // Cube VertexData

    auto cube_vinfo_id = FUG_RESOURCE_ID_MAP.getId("cube_vinfo"); 
    FUG_RESOURCE_MANAGER.addResourceInfo<Text, TextInitInfo_File>
    (cube_vinfo_id, TextInitInfo_File{"../res/meshes/cube.obj"});
   
    auto cube_vertex_id = FUG_RESOURCE_ID_MAP.getId("cube_vertex"); 
    FUG_RESOURCE_MANAGER.addResourceInfo<VertexData, VertexDataInitInfo_Text>
    (cube_vertex_id, VertexDataInitInfo_Text{VertexDataInitInfo_Text::SOURCE_BINARY_OBJ},
        {cube_vinfo_id}, {}, true);

    // Cube Mesh

    auto cube_mesh_id = FUG_RESOURCE_ID_MAP.getId("cube_mesh");   
    FUG_RESOURCE_MANAGER.addResourceInfo<Mesh, MeshInitInfo_Default>
    (cube_mesh_id, MeshInitInfo_Default(), {cube_vertex_id}, {cube_mat_id});

    // Cube MeshComponent

    static auto cubeMeshResPtr = FUG_RESOURCE_MANAGER.getResource<Mesh>(cube_mesh_id);
    return MeshComponent(cubeMeshResPtr);
}



