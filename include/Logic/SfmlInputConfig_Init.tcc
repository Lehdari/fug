FUG_RESOURCE_INIT(SfmlInputConfig, SfmlInputConfig_Init_Default)
{
    inputMap = std::move(initInfo.map);
}

FUG_RESOURCE_DESTROY(SfmlInputConfig, SfmlInputConfig_Init_Default)
{

}
