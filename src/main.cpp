#include "List.hpp"
#include <iostream>

int main() {
    try {
        std::cout << "=== Test ===\n\n";
        
        // Create a list from a file
        List original_list;
        original_list.create_list_from_file("inlet.in");
        std::cout << "Nodes created: " << original_list.count << "\n";
        
        // Print the resulting list
        std::cout << "\nOriginal list:\n";
        ListNode* current = original_list.head;
        int index = 0;
        while (current) {
            std::cout << "Node " << index << ": data=\"" << current->data << "\"";
            
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
        
        // Serialization
        original_list.serialize("outlet.out");
        std::cout << "\nSerialization completed\n";
        
        // Deserialization
        List restored_list;
        restored_list.deserialize("outlet.out");
        std::cout << "Deserialization completed\n";
        
        // Print the restored list
        std::cout << "\nRestored list:\n";
        current = restored_list.head;
        index = 0;
        while (current) {
            std::cout << "Node " << index << ": data=\"" << current->data << "\"";
            
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
        std::cerr << "\nError: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}