#pragma once

#include <iostream>
#include <typeinfo>
#include <string_view>

namespace rtti {
    // https://stackoverflow.com/questions/35941045/how-can-i-obtain-a-c-expressions-type-at-compile-time-i-e-constexprly
    // Answered by einpoklum

    template <typename T> constexpr std::string_view type_name();

    template <>
    constexpr std::string_view type_name<void>()
    {
        return "void";
    }

    namespace detail {

        using type_name_prober = void;

        template <typename T>
        constexpr std::string_view wrapped_type_name()
        {
#ifdef __clang__
            return __PRETTY_FUNCTION__;
#elif defined(__GNUC__)
            return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
            return __FUNCSIG__;
#else
#error "Unsupported compiler"
#endif
        }

        constexpr std::size_t wrapped_type_name_prefix_length() {
            return wrapped_type_name<type_name_prober>().find(type_name<type_name_prober>());
        }

        constexpr std::size_t wrapped_type_name_suffix_length() {
            return wrapped_type_name<type_name_prober>().length()
                - wrapped_type_name_prefix_length()
                - type_name<type_name_prober>().length();
        }

    } // namespace detail

    template <typename T>
    constexpr std::string_view TypeName() {
        constexpr auto wrapped_name = detail::wrapped_type_name<T>();
        constexpr auto prefix_length = detail::wrapped_type_name_prefix_length();
        constexpr auto suffix_length = detail::wrapped_type_name_suffix_length();
        constexpr auto type_name_length = wrapped_name.length() - prefix_length - suffix_length;
        return wrapped_name.substr(prefix_length, type_name_length);
    }
} // rtti
