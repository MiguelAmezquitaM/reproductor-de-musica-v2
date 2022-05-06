#pragma once
#include <cstdint>
#include <stdexcept>

namespace RDM {

    template<typename Type>
    class list {

    public: // Types
        using valuetype = Type;

    public: //Subclasses

        struct node {
        public:
            node(const valuetype& value, node* prev, node* next);
            node(const valuetype& value);
            node() = default;
            ~node(); // Destructor is called before of destroy list

            // Value of concrete node
            valuetype value;
            list<valuetype>::node* prev{ nullptr };
            list<valuetype>::node* next{ nullptr };
        };

        struct iterator { // Is used for iterate on the list easly
            iterator(node* p_node);

            node* get_node();
            valuetype& operator*();

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
        void insert_at(const valuetype& element, const uint32_t index);

        // Insert an element at last
        void push_back(const valuetype& element);

        // Insert an element at index
        void push_front(const valuetype& element);

        // Pull methods

        // Return a reference to the index-th element 
        valuetype& operator[](const uint32_t index) const;

        // Delete methods

        // Delete the last element and return it
        valuetype pop_back();

        // Delete the first element and return it
        valuetype pop_front();

        // Delete n-th element and return it
        valuetype remove_at(const uint32_t index);

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
