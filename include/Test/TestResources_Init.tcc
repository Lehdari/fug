FUG_RESOURCE_INIT(TestResource1, TestResource1_Init_Default)
{
    printf("Initializing TestResource1 with TestResource1_Init_Default\n");
    a = 1;
}

FUG_RESOURCE_DESTROY(TestResource1, TestResource1_Init_Default)
{

}

FUG_RESOURCE_INIT(TestResource2, TestResource2_Init_TestResource1)
{
    printf("Initializing TestResource1 with TestResource2_Init_TestResource1\n");
    //printf("initResources size: %llu\n", initResources.size());
    //printf("%llu\n", initResources[0]);

    auto tr1Ptr = FUG_RESOURCE_MANAGER.getResource<TestResource1>(initResources[0]);
    printf("get: %p\n", tr1Ptr.get());

    a = tr1Ptr->a;
}

FUG_RESOURCE_DESTROY(TestResource2, TestResource2_Init_TestResource1)
{

}
