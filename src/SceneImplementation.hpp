#ifndef FUG_SCENE_IMPLEMENTATION_HPP
#define FUG_SCENE_IMPLEMENTATION_HPP


namespace fug {


    template <typename... T_SceneComponents>
    class BasicScene;

    class TestComponent1;
    class TestComponent2;
    class TestComponent3;

    //  Chosen implementation
    using SceneImplementation   = BasicScene<TestComponent1, TestComponent2, TestComponent3>;


};


#endif // FUG_SCENE_IMPLEMENTATION_HPP
