#pragma once
#include <cstdint>
#include <stdexcept>

namespace RDM {

    template<typename Type>
    class list {

    public: // Types
        using ValueType = Type;

    public: //Subclasses

        struct node {
        public:
            node(const ValueType& value, node* prev, node* next);
            node(const ValueType& value);
            node() = default;
            ~node();

            // Value of concrete node
            ValueType value;
            node* prev{ nullptr };
            node* next{ nullptr };
        };

        struct iterator {
            iterator(node* p_node);

            node* get_node();
            ValueType& operator*();

            iterator& operator++(int);
            iterator& operator--(int);
            iterator& operator++();
            iterator& operator--();

            iterator& operator+=(int n);
            iterator& operator-=(int n);

            bool operator==(const iterator& other) const;
            bool operator!=(const iterator& other) const;

        private:
            node* m_node{ nullptr };
        };

    public:
        list();
        ~list();

        // Return number of elements of list
        inline uint32_t size() const noexcept;

        // Return true is list is empty
        inline bool is_empty() const noexcept;

        // Iterator methods

        // Return an iterator in first element
        inline iterator begin() const;

        // Return an iterator in last element
        inline iterator end() const;

        // Input methods

        // Insert an element in n-th index
        // No use this if list is empty
        void insert_at(const ValueType& element, const uint32_t index);

        // Insert an element at last
        void push_back(const ValueType& element);

        // Insert an element at index
        void push_front(const ValueType& element);

        // Instance an element at last
        template<typename... Args>
        void emplace_back(Args&&... args);

        // Instance an element at index
        template<typename... Args>
        void emplace_front(Args&&... args);

        // Pull methods

        // Return a reference to the index-th element 
        ValueType& operator[](const uint32_t index) const;

        // Delete methods

        // Delete the last element and return it
        ValueType pop_back();

        // Delete the first element and return it
        ValueType pop_front();

        // Delete n-th element and return it
        ValueType remove_at(const uint32_t index);

        // Remove all songs of list
        void clear();

        // Get any node of list, linear complexity
        node* get_node(uint32_t index) const;
    private:

        node* m_initial{ nullptr };
        node* m_final{ nullptr };
        uint32_t m_size{ 0 };
    };
}

#include <list.ipp> // Implementation
