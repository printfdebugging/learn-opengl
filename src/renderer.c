#include "renderer.h"

void renderer_init() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void renderer_prepare() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void renderer_render(struct mesh mesh) {
    mesh_bind(&mesh);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    mesh_unbind();
    glUseProgram(0);
}
