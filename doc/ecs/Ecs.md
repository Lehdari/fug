Class Ecs
================

Class Ecs is the core of the data-driven entity-component-system.
It facilitates game entities via components and systems:
components store entity state and systems provide entity functionality.
The ECS used is of a "pure" desing - components do not store functionality and
systems do not store state. Entities can consist of any combination of
components and systems can manipulate multiple components.

Ecs can also store singleton components - that is, components which have only one
instantiated object within the Ecs.

Class Ecs interface specification
---------------------------------

- `EntityId getEmptyEntityId()`
    - Description
        - Get an empty entity ID. That is, an ID of entity with no components.
    - Returns
        - ID of an empty entity
        
- `bool entityExists(eId)`
    - Description
        - Check if entity exists(has any components).
    - Arguments
        - `const EntityId& eId`: The ID of the entity to be checked.
    - Returns
        - Boolean indicating whether the given entity has any components
        
- `T_Component* addComponent(eId)`
    - Description
        - Add a component to an entity.
        - If the component is enabled(exists and hasn't been removed), component
          remains unchanged and handle to existing component is returned.
        - If the component is disabled(does not exist or has been removed), a pointer
          to default-constructed component is returned.
        - If the component is disabled and there is a system running, the creation
          operation is deferred and a nullptr is returned. Deferred operations are
          executed once all the systems have been run.
    - Template specification
        - `typename T_Component`: Component type
    - Arguments
        - `const EntityId& eId`: The ID of the entity to which component is to
          be added
    - Returns
        - Pointer to the component of given entity
                
- `T_Component* getComponent(eId)`
    - Description
        - Get a handle to a component of an entity.
        - If the component is disabled(does not exist or has been removed), a nullptr
          is returned.
    - Template specification
        - `typename T_Component`: Component type
    - Arguments
        - `const EntityId& eId`: The ID of the entity of which component is to
          be accessed
    - Returns
        - Pointer to the component of given entity
        
- `void setComponent(eId, component)`
    - Description
        - Assign component.
        - If the component is disabled and there is a system running, the assignment
          operation is deferred. Deferred operations are executed once all the
          systems have been run.
    - Template specification
        - `typename T_Component`: Component type
    - Arguments
        - `const EntityId& eId`: The ID of the entity of which component is to be
          assigned. 

- `T_Singleton* getSingleton()`
    - Description
        - Get a handle to singleton component.
    - Template specification
        - `typename T_Singleton`: Singleton component type
    - Returns
        - Pointer to a singleton of specified type

- `void runSystem(system)`
    - Description
        - Run a system on the ECS. Entities with specified combination
          of components are only accessed.
    - Template specification
        - `typename T_System`: System type
        - `typename... T_Components`: Component types
    - Arguments
        - `System<T_System, T_Components...>& system`: The system to run
          
- `void removeComponent(eId)`
    - Description
        - Remove a component from given entity.
        - Note: destruction of the component object is not guaranteed, so it is recommended
          to free all data managed by the component before removal.
        - If there is a system running, the removal operation is deferred. Deferred
          operations are executed once all the systems have been run.
    - Template specification
        - `typename T_Component`: Component type
    - Arguments
        - `const EntityId& eId`: The ID of the entity of which component is to
        be removed
        
- `void removeEntity(eId)`
    - Description
        - Remove an entity(disable all components).
        - Note: destruction of the component objects is not guaranteed, so it is recommended
          to free all data managed by the components before removal.
        - If there is a system running, the removal operation is deferred. Deferred
          operations are executed once all the systems have been run.
    - Arguments
        - `const EntityId& eId`: ID of the entity to be removed.
        
Component and System requirements
---------------------------------

As components are allocated internally in the Ecs, they are required to be
default constructible.

Systems need to be derived from System class using CRTP. Furthermore, `operator()`
is to be defined for references to components specified by the system template parameters.
