# TemplateECS

How?

Instantiate an ECS:
```
Ecs ecs;
```

Add components using entity ID:
```
MyLittleComponent myLittleComponent1("foo", 715517);
MyBigComponent myBigComponent1("BAR");

ecs.addComponent(0, myLittleComponent1);
ecs.addComponent(0, myBigComponent1);
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