#ifndef FUG_TYPES_HPP
#define FUG_TYPES_HPP


#include <cstdint>


namespace fug {

    using   ComponentId = uint64_t;
    using   EntityId    = uint64_t;
    using   ResourceId  = uint64_t;

	using	EventId		= uint64_t;
	using	EventPort	= uint16_t;
	using 	MailboxSize_t 	= uint16_t;

    /// Shortening typedefs
    using   CId = ComponentId;
    using   EId = EntityId;
    using   RId = ResourceId;

}


#endif // FUG_TYPES_HPP
