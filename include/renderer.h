#ifndef RENDERER_H
#define RENDERER_H

#include "mesh.h"

enum render_type {
    VERTICES = 0,
    INDICES = 1,
    VERTICES_WIREFRAME = 2,
    INDICES_WIREFRAME = 3,
};

/*
    TODO: renderer is stateless at the moment, but
    later we want to have viewport information on the
    renderer (see client.c in github.com/nitrix/layman)

    since renderer is still in wip, i am skipping the
    doc comments for these functions.
*/

void renderer_init();

void renderer_prepare();

void renderer_render(struct mesh mesh, enum render_type render_type);

#endif
