#pragma once

#include <cstddef>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "dataTypes/common.hpp"

template <typename... T>
class Table {
public:
    Table() = default;

    template<std::size_t Column>
    typename std::tuple_element<Column, std::tuple<T...>>::type& get(const size_t& row) {
        return std::get<Column>(tablev[row]);
    }

    void addRow(T&&... args) {
        tablev.push_back(std::tuple<T...>(std::forward<T>(args)...));
    }
private:
    std::vector<std::tuple<T...>> tablev;
};