#pragma once

namespace RDM {

    constexpr auto IndexOutOfRangeMessage = "Index out of range";
    constexpr auto ElementNotFounded = "Don't exist element";

    // __________________NODE IMPL_________________________________
    template<typename Type>
    list<Type>::node::node(const ValueType& value, node* prev, node* next)
        : value{ value }, prev{ prev }, next{ next } {}

    template<typename Type>
    list<Type>::node::node(const ValueType& value)
        : node(value, nullptr, nullptr) {
    }

    template<typename Type>
    list<Type>::node::~node() {
        prev = nullptr;
        next = nullptr;
    }

    // __________________ITERATOR IMPL______________________________
    template<typename Type>
    list<Type>::iterator::iterator(node* p_node)
        : m_node{ p_node } {
    }

    template<typename Type>
    typename list<Type>::node* list<Type>::iterator::get_node() { return m_node; }

    template<typename Type>
    Type& list<Type>::iterator::operator*() {
        return m_node->value;
    }

    template<typename Type>
    typename list<Type>::iterator& list<Type>::iterator::operator++(int) {
        m_node = m_node->next;
        return *this;
    }

    template<typename Type>
    typename list<Type>::iterator& list<Type>::iterator::operator--(int) {
        m_node = m_node->prev;
        return *this;
    }

    template<typename Type>
    typename list<Type>::iterator& list<Type>::iterator::operator++() {
        m_node = m_node->next;
        return *this;
    }

    template<typename Type>
    typename list<Type>::iterator& list<Type>::iterator::operator--() {
        m_node = m_node->prev;
        return *this;
    }

    template<typename Type>
    bool list<Type>::iterator::operator==(const iterator& other) const {
        return other.m_node == m_node;
    }

    template<typename Type>
    bool list<Type>::iterator::operator!=(const iterator& other) const {
        return !(other == *this);
    }

    // __________________LIST IMPL______________________________________

    template<typename Type>
    list<Type>::list() {
        node* default_element = new node();
        default_element->next = default_element;
        default_element->prev = default_element;
        m_initial = m_final = default_element;
    }

    template<typename Type>
    list<Type>::~list() {
        clear();
        delete m_initial;
        m_initial = m_final = nullptr;
    }

    template<typename Type>
    inline uint32_t list<Type>::size() const noexcept { return m_size; }

    template<typename Type>
    inline bool list<Type>::is_empty() const noexcept { return m_size == 0; }

    template<typename Type>
    inline typename list<Type>::iterator list<Type>::begin() const { return iterator(m_initial->next); }

    template<typename Type>
    inline typename list<Type>::iterator list<Type>::end() const { return iterator(m_final); }

    template<typename Type>
    void list<Type>::insert_at(const ValueType& value, const uint32_t index) {
        if (index == 0)      return push_front(value);
        if (index == m_size) return push_back(value);

        node* back_at = get_node(index);
        node* new_element_node = new node(value, back_at->prev, back_at);

        back_at->prev->next = new_element_node;
        back_at->prev = new_element_node;

        m_size++;
    }

    template<typename Type>
    void list<Type>::push_back(const ValueType& value) {
        node* new_element_node = new node(value, m_final->prev, m_final);
        m_final->prev->next = new_element_node;
        m_final->prev = new_element_node;
        m_size++;
    }

    template<typename Type>
    void list<Type>::push_front(const ValueType& value) {
        auto new_element_node = new node(value, m_initial, m_initial->next);
        m_initial->next->prev = new_element_node;
        m_initial->next = new_element_node;
        m_size++;
    }

    template<typename Type>
    Type& list<Type>::operator[](const uint32_t index) const {
        node* element_node = get_node(index);
        if (element_node == nullptr) throw std::logic_error(ElementNotFounded);
        return element_node->value;
    }

    template<typename Type>
    Type list<Type>::remove_at(const uint32_t index) {
        node* element_to_remove = get_node(index);
        ValueType element;

        m_size--;

        element_to_remove->prev->next = element_to_remove->next;
        element_to_remove->next->prev = element_to_remove->prev;

        element = element_to_remove->value;
        delete element_to_remove;
        return element;
    }

    template<typename Type>
    Type list<Type>::pop_front() {
        return remove_at(0);
    }

    template<typename Type>
    Type list<Type>::pop_back() {
        return remove_at(m_size - 1);
    }

    template<typename Type>
    void list<Type>::clear() {
        while (!is_empty()) {
            pop_front();
        }
    }

    template<typename Type>
    typename list<Type>::node* list<Type>::get_node(uint32_t index) const {
        if (index < 0 or index > m_size) throw std::out_of_range(IndexOutOfRangeMessage);
        if (index == m_size - 1) return m_final->prev;

        uint32_t it{ 0 };

        for (iterator i = begin(); i != end(); i++) {
            if (it == index)
                return i.get_node();

            it++;
        }

        return nullptr;
    }
}
