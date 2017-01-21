#ifndef FUG_VISITOR_HPP
#define FUG_VISITOR_HPP


//  macro for correct CRTP usage
#define FUG_VISITOR(VISITOR_TYPE)\
    VISITOR_TYPE : public fug::Visitor<VISITOR_TYPE>


namespace fug {


    //  Visitor class provides a CRTP interface for derived
    //  visitors for arbitrary component combinations
    template <typename T_Visitor, typename... T_Components>
    class Visitor {
    public:
        //  Functor operator taking components as a reference
        //  is implemented in derived classes.
        //  Components are being provided by scene when
        //  the visitor is accepted.
        //  The operator returns a boolean indicating whether
        //  descendants of the entity should be visited
        //  true: descendants will be visited
        //  false: descendants will be skipped
        void operator()(T_Components&... components);
    };


    template <typename T_Visitor, typename... T_Components>
    void Visitor<T_Visitor, T_Components...>::operator()(T_Components&... components)
    {
        return (*static_cast<T_Visitor*>(this))(components...);
    }


}


#endif // FUG_VISITOR_HPP
