#pragma once
#include <iostream>
#include "custom_vector.h"
#include "linked_list_node.h"
#include "key_value.h"

class JakDojadeHashMap {
public:
    JakDojadeVector<KeyValue> buckets;
    size_t bucketCount;

    JakDojadeHashMap(size_t size = 1000000) : bucketCount(size) {
        buckets.resizeVector(size);
    }

    void insertList(CityLinkedList* list) {
        size_t index = list->head->name.toHash() % bucketCount;

        CityNode *tmp = list->head;

        while (tmp != nullptr) {
            buckets[index].cityLinkedList.append(tmp);

            tmp = tmp->next;
        }

        buckets[index].filled = true;
    }

    // Insert a key-value pair into the hashmap
    void insert(CityNode *node) {
        size_t index = node->name.toHash() % bucketCount;

        CityNode *foundNode = buckets[index].cityLinkedList.findValue(node->name);

        // Node was not found
        if (foundNode != nullptr) {
            // Update weight if smaller than found
            if (foundNode->weight > node->weight) {
                foundNode->weight = node->weight;
            }

            return;
        }

        buckets[index].cityLinkedList.append(node);
    }

    // Retrieve the value associated with a given key
    CityLinkedList* operator[](JakDojadeString key) {
        size_t index = key.toHash() % bucketCount;

        return &buckets[index].cityLinkedList;
    }

    CityLinkedList* operator[](int index) {
        return &buckets[index].cityLinkedList;
    }
};