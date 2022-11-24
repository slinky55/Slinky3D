#include <iostream>
#include <vector>
#include <algorithm>

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Primitives/Icosphere.h>
#include <Magnum/Primitives/Axis.h>
#include <Magnum/Shaders/PhongGL.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/Timeline.h>

#include <Slinky/Particle/Particle.hpp>
#include <Slinky/Math/Vector3.hpp>

using namespace Magnum;

struct Projectile
{
    Matrix4 transform;
    Slinky::Particle particle;

    float lifetime {0};
};

class ParticlesExample : public Magnum::Platform::Application
{
public:
    explicit ParticlesExample(const Arguments& arguments);
    virtual ~ParticlesExample() = default;

    int Run();
private:
    void drawEvent() override;

    void keyPressEvent(KeyEvent& event) override;

    GL::Mesh sphereMesh { MeshTools::compile(Primitives::icosphereSolid(3)) };
    GL::Mesh axisMesh { MeshTools::compile(Primitives::axis3D()) };

    Shaders::PhongGL sphereShader;

    Shaders::PhongGL axisShader;
    Matrix4 axisTransform;

    Matrix4 view;
    Matrix4 projection;

    std::vector<Projectile*> projectiles;

    Timeline timeline;
};

ParticlesExample::ParticlesExample(const Arguments& arguments)
    : Magnum::Platform::Application{arguments, Configuration{}.setTitle("Particles Example")}
{
    using namespace Math::Literals;

    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);

    sphereShader.setLightPositions  ({{1.4f, 1.0f, 0.75f, 0.0f}})
            .setDiffuseColor(Color3::cyan())
            .setAmbientColor(Color3::fromHsv({Color3::cyan().hue(), 1.0f, 0.3f}));

    projection =
            Matrix4::rotationY(15.0_degf) *
            Matrix4::perspectiveProjection(
                    70.0_degf, Vector2{windowSize()}.aspectRatio(), 0.01f, 100.0f) *
                    Matrix4::translation(Vector3::zAxis(-5.0f));

    timeline.start();
}

void ParticlesExample::drawEvent()
{
    GL::defaultFramebuffer.clear(
            GL::FramebufferClear::Color|GL::FramebufferClear::Depth);

    for (auto& proj : projectiles)
    {
        proj->transform = Matrix4::translation({
            proj->particle.position.x,
            proj->particle.position.y,
            proj->particle.position.z
        }) * Matrix4::scaling({0.1f, 0.1f, 0.1f});

        sphereShader.setTransformationMatrix(proj->transform)
                .setNormalMatrix(proj->transform.normalMatrix())
                .setProjectionMatrix(projection)
                .draw(sphereMesh);
    }

    axisShader.setLightPositions  ({{1.4f, 1.0f, 0.75f, 0.0f}})
        .setTransformationMatrix(axisTransform)
        .setNormalMatrix(axisTransform.normalMatrix())
        .setProjectionMatrix(projection)
        .draw(axisMesh);

    swapBuffers();
}

void ParticlesExample::keyPressEvent(KeyEvent &event)
{
    if (event.key() == KeyEvent::Key::Space)
    {
        auto& projectile { projectiles.emplace_back( new Projectile{
            Matrix4::translation({0.f, 0.f, 0.f}),
            Slinky::Particle({0.f, 0.f, 0.f}, 2.f, 0.f, 0.99f)
        })};

        projectile->transform = Matrix4::scaling({0.1f, 0.1f, 0.1f}) * projectile->transform;

        projectile->particle.velocity = {35.f, 1.f, 0.f};
        projectile->particle.acceleration = {0.f, -1.f, 0.f};
    }
}

int ParticlesExample::Run()
{
    float dt {0.f};
    float lastTime {0.f};
    float currentTime {0.f};

    while (mainLoopIteration())
    {
        currentTime = timeline.currentFrameTime();
        dt = currentTime - lastTime;
        lastTime = currentTime;

        for (auto& proj : projectiles)
        {
            proj->lifetime += dt;

            if (proj->lifetime >= 2.f)
            {
                projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), proj), projectiles.end());
                continue;
            }

            proj->particle.Integrate(dt);
        }

        redraw();
    }

    return 0;
}

int main(int argc, char** argv)
{
    ParticlesExample app({argc, argv});
    return app.Run();
}