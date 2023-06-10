#pragma once
#include <iostream>
#include "linked_list_node.h"
#include "custom_string.h"

class CityLinkedList {
public:
    CityNode* head;
    CityNode* tail;

    CityLinkedList() : head(nullptr), tail(nullptr) {}

    CityLinkedList(const CityLinkedList& other) : head(nullptr), tail(nullptr) {
        // Copy the nodes from the other list to the new list
        CityNode* current = other.head;
        while (current != nullptr) {
            // Create a new node
            CityNode* newNode = new CityNode(current->name, current->weight);

            // Append the new node to the copied list
            append(newNode);

            current = current->next;
        }
    }


    ~CityLinkedList() {
        clear();
    }

    void append(CityNode *node) {
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            bool found = false;
            CityNode *tmp = this->head;

            while (tmp != nullptr) {
                if (!strcmp(tmp->name.c_str(), node->name.c_str())) {
                    found = true;

                    if (tmp->weight > node->weight) {
                        tmp->weight = node->weight;
                    }
                }

                tmp = tmp->next;
            }

            if (!found) {
                tail->next = node;
                tail = node;
            }
        }
    }

    void clear() {
        CityNode* current = head;
        while (current != nullptr) {
            CityNode* next = current->next;
//            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }

    CityNode* findValue(CustomString name) {
        CityNode *temp = this->head;

        while (temp != nullptr) {
            if (!strcmp(temp->name.c_str(), name.c_str())) {
                return temp;
            }

            temp = temp->next;
        }

        return nullptr;
    }

    void print() {
        if (this->head != nullptr) {
            printf("PRINTING NEIGHBORS OF %s\n", this->head->name.c_str());
            CityNode* tmp = this->head;
            if (tmp->next != nullptr) tmp = tmp->next;

            while (tmp != nullptr) {
                printf(" - %s at distance: %d\n", tmp->name.c_str(), tmp->weight);
                tmp = tmp->next;
            }
        }
    }

    CityNode* findClosestNode() {
        CityNode *tmp = this->head;

        // Ignore the first node
        tmp = tmp->next;

        CityNode *minNode = tmp;

        while (tmp != nullptr) {
            if (tmp->weight < minNode->weight) {
                minNode = tmp;
            }

            tmp = tmp->next;
        }

        return minNode;
    }

    void sort() {}
};
