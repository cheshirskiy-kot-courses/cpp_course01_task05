#pragma once

#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <string>
#include <vector>
#include <list>
#include <tuple>


class NotImplemented: public std::logic_error
{
public:
    NotImplemented(): std::logic_error{ "Function not implemented" } {};
};


// container
template<class T>
struct is_container: std::false_type {};
template<class T>
struct is_container<std::vector<T>>: std::true_type {};
template<class T>
struct is_container<std::list<T>>: std::true_type {};
template<class T>
inline constexpr bool is_container_v = is_container<T>::value;

// tuple
template<class ...Ts>
struct is_tuple: std::false_type {};
template<class ...Ts>
struct is_tuple<std::tuple<Ts...>>: std::true_type {};
template<class T>
inline constexpr bool is_tuple_v = is_tuple<T>::value;


template<class T>
std::enable_if_t<std::is_integral_v<T>>
print_ip(T ip)
{
    for (int i = sizeof(T) - 1; i > 0; --i) {
        std::cout << ((ip >> i * 8) & 0xff) << ".";
    }

    std::cout << (ip & 0xff) << std::endl;
}


template<class T>
std::enable_if_t<std::is_same_v<T, std::string>>
print_ip(const T & ip)
{
    std::cout << ip << std::endl;
}


template<class T>
std::enable_if_t<is_container_v<T>>
print_ip(const T & ip)
{
    auto last = std::prev(ip.cend());
    for (auto itr = ip.cbegin(); itr != last; ++itr) {
        std::cout << *itr << ".";
    }
    std::cout << *last << std::endl;
}


template<class T, class ...Ts>
void check_tuple(const std::tuple<T, Ts...> & ip)
{
    static_assert(std::conjunction_v<std::is_same<T, Ts>...>, "error: tuple contain date of different types");
}


template<std::size_t index = 0, class ...Ts>
void print_tuple(const std::tuple<Ts...> & ip)
{
    if constexpr (index < sizeof...(Ts) - 1) {
        std::cout << std::get<index>(ip) << ".";
        print_tuple<index + 1>(ip);
    } else {
        std::cout << std::get<index>(ip) << std::endl;
    }
}


template<class T>
std::enable_if_t<is_tuple_v<T>>
print_ip(const T & ip)
{
    check_tuple(ip);
    print_tuple(ip);
}
