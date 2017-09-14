#ifndef CWRAPPER_ENUM_HPP
#define CWRAPPER_ENUM_HPP

#include <type_traits>

namespace cwrapper
{

template <typename T>
struct EnumTraits;

// specialize this with isBitFlag = true
// to generate bit flag operators
template <typename T>
struct EnumTraits
{
    constexpr static bool isBitFlag = false;
};

} // namespace cwrapper

template <typename T, typename = std::enable_if_t<cwrapper::EnumTraits<T>::isBitFlag>>
constexpr T operator|(T lhs, T rhs)
{
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(lhs) | static_cast<std::underlying_type_t<T>>(rhs));
}

template <typename T, typename = std::enable_if_t<cwrapper::EnumTraits<T>::isBitFlag>>
constexpr T& operator|=(T& lhs, T rhs)
{
    return lhs = static_cast<T>(static_cast<std::underlying_type_t<T>>(lhs) | static_cast<std::underlying_type_t<T>>(rhs));
}

template <typename T, typename = std::enable_if_t<cwrapper::EnumTraits<T>::isBitFlag>>
constexpr inline T operator&(T lhs, T rhs)
{
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(lhs) & static_cast<std::underlying_type_t<T>>(rhs));
}

template <typename T, typename = std::enable_if_t<cwrapper::EnumTraits<T>::isBitFlag>>
constexpr inline T& operator&=(T& lhs, T rhs)
{
    return lhs = static_cast<T>(static_cast<std::underlying_type_t<T>>(lhs) & static_cast<std::underlying_type_t<T>>(rhs));
}

template <typename T, typename = std::enable_if_t<cwrapper::EnumTraits<T>::isBitFlag>>
constexpr inline T operator^(T lhs, T rhs)
{
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(lhs) ^ static_cast<std::underlying_type_t<T>>(rhs));
}

template <typename T, typename = std::enable_if_t<cwrapper::EnumTraits<T>::isBitFlag>>
constexpr inline T& operator^=(T& lhs, T rhs)
{
    return lhs = static_cast<T>(static_cast<std::underlying_type_t<T>>(lhs) ^ static_cast<std::underlying_type_t<T>>(rhs));
}

template <typename T, typename = std::enable_if_t<cwrapper::EnumTraits<T>::isBitFlag>>
constexpr inline T operator~(T sub)
{
    return static_cast<T>(~static_cast<std::underlying_type_t<T>>(sub));
}

#endif // CWRAPPER_ENUM_HPP
