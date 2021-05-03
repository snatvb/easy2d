#pragma once
#include <sole.hpp>

namespace easy2d
{
    class UUID
    {
    public:
        UUID() = default;
        explicit UUID(uint64_t ab, uint64_t cd) : _uuid{ab, cd} {}
        explicit UUID(const std::string &str) : _uuid(sole::rebuild(str)) {}

        bool operator==(const UUID &other) const { return _uuid == other._uuid; }
        bool operator!=(const UUID &other) const { return _uuid != other._uuid; }
        bool operator<(const UUID &other) const { return _uuid < other._uuid; }
        operator bool() const { return valid(); }

        std::string toString() const { return _uuid.str(); }
        void fromString(std::string str) { _uuid = sole::rebuild(str); }

        bool valid() const;
        size_t hash() const;
        const uint64_t &ab() const { return _uuid.ab; }
        const uint64_t &cd() const { return _uuid.cd; }
        static UUID generate() { return UUID(sole::uuid4()); }

    private:
        sole::uuid _uuid;

        explicit UUID(const sole::uuid &uuid) : _uuid(uuid) {}

        static const UUID INVALID;
    };
} // -- easy2d
