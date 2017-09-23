/*
   Copyright 2017 Cory Sherman

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

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
    return lhs = lhs | rhs;
}

template <typename T, typename = std::enable_if_t<cwrapper::EnumTraits<T>::isBitFlag>>
constexpr inline T operator&(T lhs, T rhs)
{
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(lhs) & static_cast<std::underlying_type_t<T>>(rhs));
}

template <typename T, typename = std::enable_if_t<cwrapper::EnumTraits<T>::isBitFlag>>
constexpr inline T& operator&=(T& lhs, T rhs)
{
    return lhs = lhs & rhs;
}

template <typename T, typename = std::enable_if_t<cwrapper::EnumTraits<T>::isBitFlag>>
constexpr inline T operator^(T lhs, T rhs)
{
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(lhs) ^ static_cast<std::underlying_type_t<T>>(rhs));
}

template <typename T, typename = std::enable_if_t<cwrapper::EnumTraits<T>::isBitFlag>>
constexpr inline T& operator^=(T& lhs, T rhs)
{
    return lhs = lhs ^ rhs;
}

template <typename T, typename = std::enable_if_t<cwrapper::EnumTraits<T>::isBitFlag>>
constexpr inline T operator~(T val)
{
    return static_cast<T>(~static_cast<std::underlying_type_t<T>>(val));
}

template <typename T, typename T2, typename = std::enable_if_t<cwrapper::EnumTraits<T>::isBitFlag>>
constexpr inline T operator<<(T lhs, T2 rhs)
{
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(lhs) << rhs);
}

template <typename T, typename T2, typename = std::enable_if_t<cwrapper::EnumTraits<T>::isBitFlag>>
constexpr inline T& operator<<=(T& lhs, T2 rhs)
{
    return lhs = lhs << rhs;
}

template <typename T, typename T2, typename = std::enable_if_t<cwrapper::EnumTraits<T>::isBitFlag>>
constexpr inline T operator>>(T lhs, T2 rhs)
{
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(lhs) >> rhs);
}

template <typename T, typename T2, typename = std::enable_if_t<cwrapper::EnumTraits<T>::isBitFlag>>
constexpr inline T& operator>>=(T& lhs, T2 rhs)
{
    return lhs = lhs >> rhs;
}

#endif // CWRAPPER_ENUM_HPP
