#ifndef FUG_TEMPLATE_UTILS
#define FUG_TEMPLATE_UTILS


#include <cstdint>


namespace fug {


    //  Integer sequence for example, unpacking tuples
    template<uint64_t ...>
    struct Sequence
    {};

    template<uint64_t N, uint64_t ...S>
    struct GenSequence : GenSequence<N-1, N-1, S...>
    {};

    template<uint64_t ...S>
    struct GenSequence<0, S...> {
      typedef Sequence<S...> type;
    };


}   //  namespace fug


#endif // FUG_TEMPLATE_UTILS
