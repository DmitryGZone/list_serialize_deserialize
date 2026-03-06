#include "List.hpp"
#include <iostream>

int main() {
    try {
        std::cout << "=== Тест ===\n\n";
        
        // Создание списка из файла
        List original_list;
        original_list.create_list_from_file("inlet.in");
        std::cout << "Создано узлов: " << original_list.count << "\n";
        
        // Вывод готового списка
        std::cout << "\nИсходный список:\n";
        ListNode* current = original_list.head;
        int index = 0;
        while (current) {
            std::cout << "Узел " << index << ": data=\"" << current->data << "\"";
            
            if (current->prev) {
                std::cout << ", prev=\"" << current->prev->data << "\"";
            } else {
                std::cout << ", prev=nullptr";
            }
            
            if (current->next) {
                std::cout << ", next=\"" << current->next->data << "\"";
            } else {
                std::cout << ", next=nullptr";
            }
            
            if (current->rand) {
                std::cout << ", rand=\"" << current->rand->data << "\"";
            } else {
                std::cout << ", rand=nullptr";
            }
            std::cout << "\n";
            
            current = current->next;
            index++;
        }
        
        // Сериализация
        original_list.serialize("outlet.out");
        std::cout << "\nСериализация завершена\n";
        
        // Десериализация
        List restored_list;
        restored_list.deserialize("outlet.out");
        std::cout << "Десериализация завершена\n";
        
        // Вывод восстановленного списка
        std::cout << "\nВосстановленный список:\n";
        current = restored_list.head;
        index = 0;
        while (current) {
            std::cout << "Узел " << index << ": data=\"" << current->data << "\"";
            
            if (current->prev) {
                std::cout << ", prev=\"" << current->prev->data << "\"";
            } else {
                std::cout << ", prev=nullptr";
            }
            
            if (current->next) {
                std::cout << ", next=\"" << current->next->data << "\"";
            } else {
                std::cout << ", next=nullptr";
            }
            
            if (current->rand) {
                std::cout << ", rand=\"" << current->rand->data << "\"";
            } else {
                std::cout << ", rand=nullptr";
            }
            std::cout << "\n";
            
            current = current->next;
            index++;
        }

        std::cout << "\n";
        
    } catch (const std::exception& e) {
        std::cerr << "\nОшибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}