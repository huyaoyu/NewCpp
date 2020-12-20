//
// Created by yaoyu on 12/20/20.
//

#ifndef SOURCECODES_TYPEUTILS_HPP
#define SOURCECODES_TYPEUTILS_HPP

#include <iostream>
#include <string_view>

#define PRINT_TYPE_NAME(s, x) \
    std::cout << "Type name of \"" << s << "\" is \"" << type_name<decltype(x)>() << "\"\n";

/**
 * Sweet function from
 * https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c/56766138#56766138
 * @tparam T The type for which the string representation is needed.
 * @return A string presentation of the template type T.
 */
template < typename T >
constexpr auto type_name() noexcept {
    std::string_view name = "Error: unsupported compiler", prefix, suffix;

#ifdef __clang__
    name = __PRETTY_FUNCTION__;
    prefix = "auto type_name() [T = ";
    suffix = "]";
#elif defined(__GNUC__)
    name = __PRETTY_FUNCTION__;
    prefix = "constexpr auto type_name() [with T = ";
    suffix = "]";
#elif defined(_MSC_VER)
    name == __FUNCSIG__;
    prefix = "auto __cdecl type_name<";
    suffix = ">(void) noexcept";
#endif
    name.remove_prefix( prefix.size() );
    name.remove_suffix( suffix.size() );

    return name;
}

#endif //SOURCECODES_TYPEUTILS_HPP
