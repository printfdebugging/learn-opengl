#include "renderer.h"
#include "logger.h"

void renderer_init() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void renderer_prepare() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void renderer_render(struct mesh mesh) {
    if (!mesh_bind(&mesh)) {
        // TODO: as renderer evolves we would want to handle this error properly
        // but for now a message is good enough, although it should not be here
        // as the error would already be reported by the functions called by
        // mesh_bind.
        ERROR("failed to bind mesh successfully during render\n");
        return;
    }
    glDrawArrays(GL_TRIANGLES, 0, 3);
    mesh_unbind();
}
