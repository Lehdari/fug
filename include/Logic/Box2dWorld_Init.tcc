FUG_RESOURCE_INIT(Box2dWorld, Box2dWorld_Init_Default)
{
    if (world == nullptr) {
        world = new b2World(initInfo.gravity);
        Box2dBodyComponent::world = world;
    }
    std::cerr << world << std::endl;
}

FUG_RESOURCE_DESTROY(Box2dWorld, Box2dWorld_Init_Default)
{
    if (world != nullptr) {
        delete world;
        world = nullptr;
        Box2dBodyComponent::world = nullptr;
    }
}
