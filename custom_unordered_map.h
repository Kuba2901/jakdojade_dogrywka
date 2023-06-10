#pragma once
#include <iostream>
#include "custom_vector.h"
#include "linked_list_node.h"
#include "key_value.h"

class CustomUnorderedMap {
public:
    CustomVector<KeyValue> buckets;
    size_t bucketCount;

    CustomUnorderedMap(size_t size = 100) : bucketCount(size) {
        buckets.resize(size);
    }

    void insertList(CityLinkedList* list) {
        size_t index = list->head->name.toHash() % bucketCount;

        CityNode *tmp = list->head;

        while (tmp != nullptr) {
            buckets[index].cityLinkedList.append(tmp);

            tmp = tmp->next;
        }

        buckets[index].filled = true;
//        printf("INSERING CITY(%s) AT INDEX: %d\n", list->head->name.c_str(), index);
    }

    // Insert a key-value pair into the hashmap
    void insert(CityNode *node) {
        size_t index = node->name.toHash() % bucketCount;

        CityNode *foundNode = buckets[index].cityLinkedList.findValue(node->name);

        // Node was not found
        if (foundNode != nullptr) {
            printf("FOUND\n");
            // Update weight if greater than found
            if (foundNode->weight > node->weight) {
                foundNode->weight = node->weight;
            }

            return;
        }

        // If the key doesn't exist, insert a new key-value pair
        buckets[index].cityLinkedList.append(node);
    }

    // Retrieve the value associated with a given key
    CityLinkedList* operator[](CustomString key) {
        size_t index = key.toHash() % bucketCount;

        return &buckets[index].cityLinkedList;
    }

    CityLinkedList* operator[](int index) {
        return &buckets[index].cityLinkedList;
    }
};