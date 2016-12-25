#ifndef FUG_VISITOR_HPP
#define FUG_VISITOR_HPP


namespace fug {


    template <typename T_Visitor, typename... T_Components>
    class Visitor {
    public:
        void operator()(T_Components&... components);
    };


    template <typename T_Visitor, typename... T_Components>
    void Visitor<T_Visitor, T_Components...>::operator()(T_Components&... components)
    {
        (*static_cast<T_Visitor*>(this))(components...);
    }


}


#endif // FUG_VISITOR_HPP
