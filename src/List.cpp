#include "List.hpp"
#include "ListNode.hpp"
#include <vector>
#include <exception>
#include <fstream>
#include <unordered_map>
#include <cstdint>

List::~List() {
    ListNode* current = head;
    while (current) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
}

void List::create_list_from_file(const std::string& inlet_file) {
    std::vector<ListNode*> nodes;

    // вектор пар для записи data / rand
    std::vector<std::pair<std::string, int>> parsed_node;
    // строка для сохранения значений из файла
    std::string line;

    std::ifstream ifs(inlet_file);
    if(!ifs.is_open()) throw std::runtime_error("Cannot open file: " + inlet_file);

    while (std::getline(ifs, line)) {
        size_t pos = line.find_last_of(';');
        if (pos == std::string::npos) throw std::runtime_error("Invalid line format: " + line);
        std::string data = line.substr(0, pos);
        int rand_index = std::stoi(line.substr(pos + 1));
        parsed_node.push_back({data, rand_index});
    }

    ifs.close();

    for (size_t i = 0; i < parsed_node.size(); i++) {
        nodes.push_back(new ListNode());
    }

    for (size_t i = 0; i < parsed_node.size(); i++) {
        nodes[i]->data = parsed_node[i].first;
        
        if (parsed_node[i].second >= 0 && parsed_node[i].second < parsed_node.size()) {
            nodes[i]->rand = nodes[parsed_node[i].second];
        }

        if (i > 0) nodes[i]->prev = nodes[i - 1];
        if (i < parsed_node.size() - 1) nodes[i]->next = nodes[i + 1]; // потому что крайние - nullptr
    }

    if (!nodes.empty()) {
        head = nodes[0];
        tail = nodes[nodes.size() - 1];
        count = nodes.size();
    }
}

void List::serialize(const std::string& outlet_file) {
    // Систематизируем rand индексы
    std::unordered_map<ListNode*, int> node_to_index;
    ListNode* current = head;
    int idx = 0;
    while (current) {
        node_to_index[current] = idx++;
        current = current->next;
    }
    
    std::ofstream ofs(outlet_file, std::ios::binary);
    if(!ofs.is_open()) throw std::runtime_error("Cannot open file: " + outlet_file);

    uint32_t node_count = static_cast<uint32_t>(count);
    ofs.write(reinterpret_cast<const char*>(&node_count), sizeof(node_count));
    
    current = head;
    while (current) {
        // Записываем data
        uint32_t len = current->data.length();
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        ofs.write(current->data.c_str(), len);
        
        // Записываем rand
        int rand_idx = -1;
        if (current->rand) {
            rand_idx = node_to_index[current->rand];
        }
        ofs.write(reinterpret_cast<const char*>(&rand_idx), sizeof(rand_idx));
        
        current = current->next;
    }
    ofs.close();
}

void List::deserialize(const std::string& outlet_file) {
    std::ifstream ifs(outlet_file, std::ios::binary);
    if (!ifs.is_open()) {
        throw std::runtime_error("Cannot open file: " + outlet_file);
    }
    
    // Читаем количество узлов
    uint32_t node_count;
    ifs.read(reinterpret_cast<char*>(&node_count), sizeof(node_count));
    if (!ifs) {
        throw std::runtime_error("Failed to read node count");
    }
    
    // Очищаем текущий список, если он не пуст
    ListNode* current = head;
    while (current) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    count = 0;
    
    std::vector<std::pair<ListNode*, int>> node_data(node_count);
    
    // Читаем данные каждого узла
    for (uint32_t i = 0; i < node_count; i++) {
        // Читаем длину строки data
        uint32_t data_len;
        ifs.read(reinterpret_cast<char*>(&data_len), sizeof(data_len));
        
        // Читаем data
        std::string data(data_len, '\0');
        ifs.read(&data[0], data_len);
        if (!ifs) {
            for (uint32_t j = 0; j < i; j++) {
                delete node_data[j].first;
            }
            throw std::runtime_error("Failed to read data");
        }
        
        // Читаем rand
        int rand_idx;
        ifs.read(reinterpret_cast<char*>(&rand_idx), sizeof(rand_idx));
        if (!ifs) {
            for (uint32_t j = 0; j < i; j++) {
                delete node_data[j].first;
            }
            throw std::runtime_error("Failed to read rand index");
        }
        
        // Создаем новый узел
        node_data[i].first = new ListNode();
        node_data[i].first->data = data;
        node_data[i].second = rand_idx;
    }
    
    ifs.close();
    
    // Связи prev/ next
    for (uint32_t i = 0; i < node_count; i++) {
        if (i > 0) {
            node_data[i].first->prev = node_data[i - 1].first;
        }
        if (i < node_count - 1) {
            node_data[i].first->next = node_data[i + 1].first;
        }
    }
    
    // Связи rand
    for (uint32_t i = 0; i < node_count; i++) {
        int rand_idx = node_data[i].second;
        if (rand_idx >= 0 && static_cast<uint32_t>(rand_idx) < node_count) {
            node_data[i].first->rand = node_data[rand_idx].first;
        }
        // rand по умолчанию - nullptr
    }
    
    // Устанавливаем head, tail и count
    if (node_count > 0) {
        head = node_data[0].first;
        tail = node_data[node_count - 1].first;
        count = static_cast<int>(node_count);
    }
}