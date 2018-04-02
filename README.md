# TemplateECS

How?

Instantiate an ECS:
```
Ecs ecs;
```

Add an entity:
```
ecs.addEntity();
```

Add components:
```
MyLittleComponent myLittleComponent1("foo", "bar", 715517);
ecs.addComponent(myLittleComponent1);
```

Define a system:
```
TECS_SYSTEM(MyLittleSystem, MyLittleComponent, MyBigComponent) {
    void operator()(MyLittleComponent& c1, MyBigComponent& c2) {
        c1.doSomething();
        c2.doSomethingElse();
    }
};
```

Run the system:
```
MyLittleSystem myLittleSystem;
ecs.runSystem(myLittleSystem);
```

Could it be so easy? Yes it can! Brought to you by C++17!