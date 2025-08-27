#ifndef MESH_H
#define MESH_H

enum mesh_attribute {
    MESH_ATTRIBUTE_POSITION = 0,
};

static const char* shader_var_names[] = {
    [MESH_ATTRIBUTE_POSITION] = "vertex_position",
};

#endif
