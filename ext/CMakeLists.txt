add_subdirectory(TemplateECS)
add_subdirectory(vecmat)
add_subdirectory(glsprite)
# This is needed to link from shared libs
set_target_properties(glsprite PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(glsprite-glutil PROPERTIES POSITION_INDEPENDENT_CODE ON)
