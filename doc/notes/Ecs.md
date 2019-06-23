ECS Desing Notes
================

Class Ecs is the core of the data-driven entity-component-system.
It facilitates game entities via components and systems:
components store entity state and systems provide entity functionality.
The ECS used is of a "pure" desing - components do not store functionality and
systems do not store state. Entities can consist of and systems can manipulate
multiple components.

Class Ecs interface specification
---------------------------------

- `EntityId getEmptyEntityId()`
    - Description
        - Get an empty entity ID. That is, an ID of entity with no components.
    - Returns
        - ID of an empty entity
        
- `T_Component* getComponent(eId)`
    - Description
        - Get a handle to a component of an entity.
    - Template specification
        - `typename T_Component`: Component type
    - Arguments
        - `const EntityId& eId`: The ID of the entity of which component is to
        be accessed
    - Returns
        - Pointer to the component of given entity
        
- `void removeComponent(eId)`
    - Description
        - Remove a component once there is no system running (deferred removal).
    - Template specification
        - `typename T_Component`: Component type
    - Arguments
        - `const EntityId& eId`: The ID of the entity of which component is to
        be removed
        
- `T_Component* getSingleton()`
    - Description
        - Get a handle to a singleton component.
    - Template specification
        - `typename T_Component`: Component type
    - Returns
        - Pointer to the singleton component

- `void runSystem(system)`
    - Description
        - Run a system on the ECS. Entities with specified combination
          of components are only accessed.
    - Template specification
        - `typename T_System`: System type
        - `typename... T_Components`: Component types
    - Arguments
        - `System<T_System, T_Components...>& system`: The system to run
        
Component and System requirements
---------------------------------

As components are allocated internally in the Ecs, they are required to be
default constructible.

Systems need to be derived from System class using CRTP. Furthermore, `operator()`
is to be defined for references to components specified by the system template parameters.
