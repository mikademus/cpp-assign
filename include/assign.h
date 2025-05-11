#pragma once

#include <tuple>
#include <utility>
#include <type_traits>
#include <concepts>

// Concept for tuple-like types (supports std::get and std::tuple_size)
template<typename T>
concept tuple_like = requires(T t) 
{
    std::tuple_size<T>::value; // Has tuple size
    std::get<0>(t);           // Supports std::get
};

// Concept to ensure each tuple element is assignable to the corresponding variable
template<typename Var, typename TupElem>
concept assignable_from = std::assignable_from<Var&, TupElem>;

// Helper class to hold references and assign from tuple-like types
template<typename... Vars>
class assign_helper 
{
public:
    // Constructor takes references to variables
    assign_helper(Vars&... vars) : refs(vars...) {}

    // Assignment operator for TupleLike types
    template<tuple_like Tup>
    requires (sizeof...(Vars) == std::tuple_size_v<Tup>) &&
             requires {
                 []<std::size_t... Is>(std::index_sequence<Is...>) {
                     return (assignable_from<Vars, std::tuple_element_t<Is, Tup>> && ...);
                 }(std::index_sequence_for<Vars...>{});
             }

    assign_helper& operator=(const Tup& tup) 
    {
        assign_impl(tup, std::index_sequence_for<Vars...>{});
        return *this;
    }

private:
    // Store references to variables
    std::tuple<Vars&...> refs;

    // Implementation of assignment using index sequence
    template<typename Tuple, std::size_t... Is>
    void assign_impl(const Tuple& tup, std::index_sequence<Is...>) 
    {
        ((std::get<Is>(refs) = std::get<Is>(tup)), ...);
    }
};

//----------------------------------------------------------------------------
// assign
//----------------------------------------------------------------------------
template<typename... Vars>
assign_helper<Vars...> assign(Vars&... vars) 
{
    return assign_helper<Vars...>(vars...);
}
