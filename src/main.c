#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ERROR(message, ...)                                \
    fprintf(stderr, "%s:%i: error: ", __FILE__, __LINE__); \
    fprintf(stderr, message, ##__VA_ARGS__)

static void framebuffer_resize_callback(GLFWwindow *window, int width, int height) {
    (void) window;
    glViewport(0, 0, width, height);
}

static void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

static const char *read_shader_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        ERROR("failed to read shader file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (length < 0) {
        fclose(file);
        ERROR("failed to get the shader file's length: %s\n", filename);
        return NULL;
    }

    char *buffer = malloc(length + 1);
    if (!buffer) {
        fclose(file);
        ERROR("failed to allocate memory for shader file: %s\n", filename);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);

    return buffer;
}

int main() {
    if (!glfwInit()) {
        ERROR("failed to initialize glfw");
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if (!window) {
        ERROR("failed to create glfw winodw\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        ERROR("failed to initialize glad\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    /* create a vertex shader */
    const GLchar *vertex_shader_source = read_shader_file("assets/shaders/shader.vert");
    if (!vertex_shader_source) return EXIT_FAILURE;

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    free((void *) vertex_shader_source);

    GLint success_vert;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success_vert);
    if (!success_vert) {
        GLint info_log_length;
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar info_log[info_log_length];
        glGetShaderInfoLog(vertex_shader, info_log_length, NULL, info_log);

        ERROR("failed to compile vertex shader: %s\n", info_log);
        return EXIT_FAILURE;
    }

    /* create a fragment shader */
    const GLchar *fragment_shader_source = read_shader_file("assets/shaders/shader.frag");
    if (!fragment_shader_source) return EXIT_FAILURE;

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    free((void *) fragment_shader_source);

    GLint success_frag;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success_frag);
    if (!success_frag) {
        GLint info_log_length;
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar info_log[info_log_length];
        glGetShaderInfoLog(fragment_shader, info_log_length, NULL, info_log);

        ERROR("failed to compile fragment shader: %s\n", info_log);
        return EXIT_FAILURE;
    }

    /* create a shader program */
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    /* bind variables to certain slot locations in the vao */
    glBindAttribLocation(shader_program, 0, "_position");
    glBindAttribLocation(shader_program, 1, "_color");
    glBindAttribLocation(shader_program, 2, "_uv");
    glLinkProgram(shader_program);

    GLint success_prog;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success_prog);
    if (!success_prog) {
        GLint info_log_length;
        glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar info_log[info_log_length];
        glGetProgramInfoLog(shader_program, info_log_length, NULL, info_log);

        ERROR("failed to link shader program: %s\n", info_log);
        return EXIT_FAILURE;
    }

    /* delete the vertex and fragment shader objects, they are ref counted internally */
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glUseProgram(shader_program);

    /* create a vao */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    /* clang-format off */
    GLfloat vertices[] = {
         // vertices          // colors             // texture coordinates
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,     1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,     0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,     1.0f, 0.0f,
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3,
    };
    /* clang-format on */

    /* create a vbo */
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* create an index buffer */
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /* bind the vbo to a slot on the vao.
     * as we keep adding more and more data to the same vbo,
     * we need to update the stride for each attribute.
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* set texture wrapping and filtering options */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned int TEXTURE0;  // maps to 0
    unsigned int TEXTURE1;  // maps to 1

    {
        /* create a texture object */
        glGenTextures(1, &TEXTURE0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TEXTURE0);

        /* load image into memory */
        int width, height, nchannels;
        stbi_set_flip_vertically_on_load(GL_TRUE);
        unsigned char *data = stbi_load("assets/textures/container.jpg", &width, &height, &nchannels, 0);
        if (!data) return EXIT_FAILURE;

        /* bind texture data to the texture object */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        /* free the image memory */
        stbi_image_free(data);
    }
    {
        /* create a texture object */
        glGenTextures(1, &TEXTURE1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, TEXTURE1);

        /* load image into memory */
        int width, height, nchannels;
        unsigned char *data = stbi_load("assets/textures/awesomeface.png", &width, &height, &nchannels, 0);
        if (!data) return EXIT_FAILURE;

        /* bind texture data to texture1 object */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        /* free awesomeface.png */
        stbi_image_free(data);
    }
    {
        {
            GLint TEXTURE0_loc = glGetUniformLocation(shader_program, "TEXTURE0");
            if (TEXTURE0_loc == -1) {
                ERROR("no uniform named TEXTURE0 found in shader_program\n");
                return EXIT_FAILURE;
            }
            glUniform1i(TEXTURE0_loc, 0);
        }
        {
            GLint TEXTURE1_loc = glGetUniformLocation(shader_program, "TEXTURE1");
            if (TEXTURE1_loc == -1) {
                ERROR("no uniform named TEXTURE1 found in shader_program\n");
                return EXIT_FAILURE;
            }
            glUniform1i(TEXTURE1_loc, 1);
        }
    }

    while (!glfwWindowShouldClose(window)) {
        /* event */
        glfwPollEvents();
        process_input(window);
        /* event */

        /* renderer */
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, NULL);
        /* renderer */

        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader_program);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &vao);
    glfwTerminate();

    return EXIT_SUCCESS;
}
