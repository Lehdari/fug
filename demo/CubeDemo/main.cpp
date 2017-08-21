
#include "main.hpp"

int main()
{
    Canvas_SFML canvas;

    ResourceLoader res("cubedemo.stfu");
    res.load();
    
    sf::SoundBuffer sbuf;
	if (!sbuf.loadFromFile(std::string(FUG_RES_DIRECTORY) + "../res/audio/bileet.wav")) {
		return -1;
	}

	sf::Sound sound;
	sound.setBuffer(sbuf);
	sound.play();

    ControlMapComponent ctrl_comp;
    ctrl_comp.map = {{sf::Keyboard::W, ControlMapComponent::Action::MoveUp},
                     {sf::Keyboard::S, ControlMapComponent::Action::MoveDown},
                     {sf::Keyboard::A, ControlMapComponent::Action::MoveLeft},
                     {sf::Keyboard::D, ControlMapComponent::Action::MoveRight}};

    auto cube_mesh_ptr = FUG_RESOURCE_MANAGER.getResource<Mesh>(FUG_RESOURCE_ID_MAP.getId("cube_mesh"));
    auto floor_mesh_ptr = FUG_RESOURCE_MANAGER.getResource<Mesh>(FUG_RESOURCE_ID_MAP.getId("floor_mesh"));

    FUG_SCENE.addEntity();
    FUG_SCENE.addComponent(BeatComponent(BeatComponent::FlashBg, 0.3f, 0.04f));
    FUG_SCENE.addComponent(TransformComponent());

    FUG_SCENE.addEntity();
    FUG_SCENE.addComponent(MeshComponent(cube_mesh_ptr));
    FUG_SCENE.addComponent(MotionComponent({0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 0.008f, -0.015f, 0.01f}));
    FUG_SCENE.addComponent(TransformComponent({0.f, 2.f, 0.f}));
    FUG_SCENE.addComponent(BeatComponent(BeatComponent::Pulse, 0.2f, 0.02f));

    FUG_SCENE.addEntity();
    FUG_SCENE.addComponent(MeshComponent(floor_mesh_ptr));
    FUG_SCENE.addComponent(TransformComponent({0.f, 0.f, 0.f}, {1.f, 1.f, 0.f, 0.f}, {10.f, 10.f, 10.f}));

    FUG_SCENE.addEntity();
    FUG_SCENE.addComponent(TransformComponent({4.f, 4.f, -4.f}, {1.f, -1.f, -0.5f, 1.f}));
    FUG_SCENE.addComponent(CameraComponent(90.f, 1280/720.f, 1.f, 50.f));
    FUG_SCENE.addComponent(std::move(ctrl_comp));

    ControlVisitor control_visitor;
    TransformVisitor transform_visitor;
    MotionVisitor motion_visitor;
    BeatVisitor beat_visitor(sound);
    CameraVisitor camera_visitor;
    RenderVisitor render_visitor;

    FUG_SCENE.accept(camera_visitor);
    render_visitor.initCamera();

    while (canvas.isOpen()) {

        // Handle window events
        canvas.handleEvents();

        // Clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Handle inputs
        FUG_SCENE.accept(control_visitor);
        
        // Handle effects
        FUG_SCENE.accept(beat_visitor);

        // Handle motions
        FUG_SCENE.accept(motion_visitor);

        // Handlle camera(s)
        FUG_SCENE.accept(camera_visitor);

        // Handle transforms
        FUG_SCENE.accept(transform_visitor);

        // Handle renders
        FUG_SCENE.accept(render_visitor);

        // Flush event buffers
        FUG_EVENT_MANAGER.flushEvents<sf::Event>(sf::Event::KeyPressed);
        FUG_EVENT_MANAGER.flushEvents<sf::Event>(sf::Event::KeyReleased);
       
        // End the current frame (internally swaps the front and back buffers)
        canvas.display();
    }
    return 0;
}
