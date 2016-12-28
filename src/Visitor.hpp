#ifndef FUG_VISITOR_HPP
#define FUG_VISITOR_HPP


namespace fug {


    //  Visitor class provides a CRTP interface for derived
    //  visitors for arbitrary component combinations
    template <typename T_Visitor, typename... T_Components>
    class Visitor {
    public:
        //  Functor operator taking components as a reference
        //  is implemented in derived classes.
        //  Components are being provided by cene when
        //  the visitor is accepted.
        void operator()(T_Components&... components);
    };


    template <typename T_Visitor, typename... T_Components>
    void Visitor<T_Visitor, T_Components...>::operator()(T_Components&... components)
    {
        (*static_cast<T_Visitor*>(this))(components...);
    }


}


#endif // FUG_VISITOR_HPP
