#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>

class Camera;
class Light;
class Model;
class HDRI;

class RenderTarget;
class AuraCompositingEffect;

class Renderer {
    public:
        Renderer(int width, int height, std::unique_ptr<Camera>&& camera);

        Renderer(Renderer&& other) = default;
        Renderer& operator=(Renderer&& other) = default;

        Renderer(const Renderer& other) = delete;
        Renderer& operator=(const Renderer& other) = delete;

        void addModel(std::shared_ptr<Model> model);
        void addLight(std::shared_ptr<Light> light);

        void render();

        void updateCameraRotation(glm::vec3 r);

        ~Renderer();
    private:
        SDL_Window* window = nullptr;

        int width;
        int height;

        std::unique_ptr<Camera> camera;

        std::vector<std::shared_ptr<Model>> models;

        std::vector<std::shared_ptr<Light>> lights;

        std::unique_ptr<RenderTarget> auraTarget;
        std::unique_ptr<RenderTarget> sceneTarget;

        std::unique_ptr<AuraCompositingEffect> auraEffect;

        struct {
            GLuint vertexArray = 0;
            GLuint vertexBuffer = 0;
            GLuint uvBuffer = 0;
        } screenObject;


        bool initializeSDL();
        bool initializeGL();

        void initializeScreenObject();
};
