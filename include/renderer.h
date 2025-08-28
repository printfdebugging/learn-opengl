#ifndef RENDERER_H
#define RENDERER_H

#include "mesh.h"

/*
    TODO: renderer is stateless at the moment, but
    later we want to have viewport information on the
    renderer (see client.c in github.com/nitrix/layman)

    since renderer is still in wip, i am skipping the 
    doc comments for these functions.
*/

void renderer_init();

void renderer_prepare();

void renderer_render(struct mesh mesh);

#endif
