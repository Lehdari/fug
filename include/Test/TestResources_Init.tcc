FUG_RESOURCE_INIT(TestResource1, TestResource1_Init_Default)
{
    printf("Initializing TestResource1 with TestResource1_Init_Default\n");
    printf("InitInfo: a: %d b: %d\n", initInfo.a, initInfo.b);
    printf("InitResources: {");
    for (auto& r : initResources)
        printf("%llu,", r);
    printf("}\n");
}

FUG_RESOURCE_DESTROY(TestResource1, TestResource1_Init_Default)
{
    printf("Destroying TestResource1(TestResource1_Init_Default)\n");
}


FUG_RESOURCE_INIT(TestResource2, TestResource2_Init_TestResource1)
{
    printf("Initializing TestResource1 with TestResource2_Init_TestResource1\n");
    printf("InitInfo: a: %0.4f b: %0.4f\n", initInfo.a, initInfo.b);
    printf("InitResources: {");
    for (auto& r : initResources)
        printf("%llu,", r);
    printf("}\n");

    auto tr1Ptr = FUG_RESOURCE_MANAGER.getResource<TestResource1>(initResources[0]);

    printf("initResource[0]: a: %d b: %d\n", tr1Ptr->a, tr1Ptr->b);

    a = tr1Ptr->a;
    b = tr1Ptr->b;
}

FUG_RESOURCE_DESTROY(TestResource2, TestResource2_Init_TestResource1)
{
    printf("Destroying TestResource1(TestResource2_Init_TestResource1)\n");
}


FUG_RESOURCE_INIT(TestResource3, TestResource3_Init_TestResource2)
{
    printf("Initializing TestResource2 with TestResource3_Init_TestResource2\n");
    printf("InitInfo: a: %0.4f b: %0.4f\n", initInfo.a, initInfo.b);
    printf("InitResources: {");
    for (auto& r : initResources)
        printf("%llu,", r);
    printf("}\n");

    auto tr1Ptr = FUG_RESOURCE_MANAGER.getResource<TestResource2>(initResources[0]);

    a = tr1Ptr->a;
    b = tr1Ptr->b;
}

FUG_RESOURCE_DESTROY(TestResource3, TestResource3_Init_TestResource2)
{
    printf("Destroying TestResource2(TestResource3_Init_TestResource2)\n");
}
