#include <limits>
#include <easy2d/Core/UUID.hpp>

namespace easy2d
{

    bool UUID::valid() const
    {
        return (_uuid.ab != (std::numeric_limits<uint64_t>::max)()) && (_uuid.cd != (std::numeric_limits<uint64_t>::max)());
    }

    size_t UUID::hash() const
    {
        std::hash<sole::uuid> h;
        return h(_uuid);
    }

} // -- easy2d
