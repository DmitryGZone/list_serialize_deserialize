#pragma once

#include <iostream>
#include <string>
#include "ListNode.hpp"
#include <fstream>

class List {
public:
    ListNode* head {nullptr};
    ListNode* tail {nullptr};
    int count {0};

    List() = default;
    ~List();
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    void create_list_from_file(const std::string& inlet_file);
    void serialize(const std::string& outlet_file);
    void deserialize(const std::string& outlet_file);
};