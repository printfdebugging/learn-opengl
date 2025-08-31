#include "renderer.h"
#include "logger.h"

void renderer_init() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void renderer_prepare() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void renderer_render(struct mesh mesh, enum render_type render_type) {
    if (!mesh_bind(&mesh)) {
        // TODO: as renderer evolves we would want to handle this error properly
        // but for now a message is good enough, although it should not be here
        // as the error would already be reported by the functions called by
        // mesh_bind.
        ERROR("failed to bind mesh successfully during render\n");
        return;
    }

    switch (render_type) {
        case VERTICES:
            glDrawArrays(GL_TRIANGLES, 0, mesh.vbo_size);
            break;
        case INDICES:
            glDrawElements(GL_TRIANGLES, mesh.ebo_size, GL_UNSIGNED_INT, 0);
            break;
        case VERTICES_WIREFRAME:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            renderer_render(mesh, VERTICES);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case INDICES_WIREFRAME:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            renderer_render(mesh, INDICES);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
    }

    mesh_unbind();
}
