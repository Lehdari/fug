FUG_RESOURCE_INIT(Box2dWorld, Box2dWorld_Init_Default)
{
    world = new b2World(initInfo.gravity);
    Box2dBodyComponent::world = world;
}

FUG_RESOURCE_DESTROY(Box2dWorld, Box2dWorld_Init_Default)
{
    delete world;
    Box2dBodyComponent::world = nullptr;
}
