#include "Renderer.h"

int GLRenderer::width = 0;

int GLRenderer::height = 0;


GLRenderer::GLRenderer(const int& w, const int& h)
{
    width = w;
    height = h;
}


bool GLRenderer::start()
{
    if (!initWindow()) return false;
    initProgram(program, "basic.vert", "basic.frag");
    init();

    while (!shouldClose)
    {
        float dt = 1 / 60.0f;
        onRender(dt);
        onProcessEvent();
        onUpdate(dt);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return true;
}

GLRenderer::~GLRenderer()
{
    glDeleteProgram(program.id);
}


bool GLRenderer::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Running Santa 3D", nullptr, nullptr);
    if (!window) {
        std::cerr << "Unable to create opengl Window";
        return false;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    return true;
}

bool GLRenderer::init()
{
    spritesheet = createTexture("spritesheet.png", 4);
    floor.init();
    Obstacle::init();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glClearColor(69.0f / 255, 148.0f / 255, 238.0f / 255, 1);
    glViewport(0, 0, width, height);
    return true;
}

bool GLRenderer::onRender(float dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program.id);
    auto projLocation = glGetUniformLocation(program.id, "mProjection");
    auto viewLocation = glGetUniformLocation(program.id, "mView");
    auto textureLocation = glGetUniformLocation(program.id, "texture");

    spritesheet->bind(textureLocation);

    auto mProjection = mat4::perspective(45 * 3.14159f / 180, float(width) / height, 0.1f, 50.0f);
    auto mView = mat4::lookAt({ 0.0f, 0.5f, 0.0f }, { 0.0f, 0.0f, -3.0f }, { 0.0f, 1.0f, 0.0f });

    glUniformMatrix4fv(projLocation, 1, false, mProjection.data());
    glUniformMatrix4fv(viewLocation, 1, false, mView.data());

    floor.render();
    Obstacle::render();

    return true;
}

bool GLRenderer::onUpdate(float dt)
{
    const float speed = 1.0f;
    floor.update(dt, 0.0f);
    Obstacle::update(dt, speed);
    return true;
}

bool GLRenderer::onProcessEvent()
{
    return true;
}


bool GLRenderer::initProgram(Program& program, const std::string& vSourcePath, const std::string& fSourcePath)
{
    auto getFile = [](const std::string& path) -> std::string {
        std::fstream file{ path };
        std::string content{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>{} };
        file.close();
        return content;
        };

    int status = 0;
    char infoLog[512]{};

    auto initShader = [&status, &infoLog](unsigned int& shader, GLenum type, const std::string& source) {
        shader = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (!status) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << (type == GL_VERTEX_SHADER ? "VERTEX_SHADER_ERROR" : "FRAGMENT_SHADER_ERROR")
                << " :: " << infoLog << std::endl;
            return false;
        }

        return true;
        };

    auto vSource = getFile(vSourcePath);
    auto fSource = getFile(fSourcePath);

    unsigned int vShader, fShader;
    initShader(vShader, GL_VERTEX_SHADER, vSource);
    initShader(fShader, GL_FRAGMENT_SHADER, fSource);

    program.id = glCreateProgram();
    glAttachShader(program.id, vShader);
    glAttachShader(program.id, fShader);
    glLinkProgram(program.id);

    glGetProgramiv(program.id, GL_LINK_STATUS, &status);
    if (!status) {
        glGetProgramInfoLog(program.id, 512, nullptr, infoLog);
        std::cerr << "PROGRAM_ERROR:: " << infoLog << std::endl;
        return false;
    }

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return true;
}
