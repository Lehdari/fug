//
// Created by Lehdari on 6.4.2019.
//

#ifndef ECSTESTGAME_LOGICCOMPONENT_HPP
#define ECSTESTGAME_LOGICCOMPONENT_HPP


struct LogicComponent {
    LogicComponent();
    ~LogicComponent();

    template <typename T_Logic>
    void addLogic();

private:
    void*   _logic;
    void    (*_logicDeleter)(void*);

    template <typename T_Logic>
    static void deleteLogic(void* logic);
};


template<typename T_Logic>
void LogicComponent::addLogic()
{
    _logic = new T_Logic();
}

template<typename T_Logic>
void LogicComponent::deleteLogic(void *logic)
{
    delete logic;
}


#endif //ECSTESTGAME_LOGICCOMPONENT_HPP
