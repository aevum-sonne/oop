#pragma once

#include <cstddef>
#include <ostream>
#include <sstream>

template <typename T>
class MyList
{
public:
    struct ListNode
    {
    public:
        ListNode() = default;

        explicit ListNode(const T& value)
                : data(value)
        {
        }

        ListNode(const T& value, ListNode* ptr)
                : data(value)
                , next(ptr)
        {
        }

        ~ListNode() = default;

        T data;
        ListNode* next = nullptr;
        ListNode* prev = nullptr;
    };

    class ListIterator
    {
        friend class MyList;

    public:
        using list_iterator = ListIterator;
        using difference_type = ptrdiff_t;

    public:
        ListIterator() = default;

        ListIterator(list_iterator& other)
                : m_item(other.m_item)
        {
        }

        T& operator*() const
        {
            return m_item->data;
        }

        list_iterator& operator+=(difference_type offset)
        {
            m_item->data += offset;

            return *this;
        }

        list_iterator operator+(difference_type offset) const
        {
            list_iterator it(m_item);

            return it += offset;
        }

        friend list_iterator operator+(difference_type offset, const list_iterator& it)
        {
            return it + offset;
        }

        list_iterator& operator++()
        {
            ListIterator::m_item = ListIterator::m_item->next;

            return *this;
        }

        list_iterator operator++(int) &
        {
            ListIterator it(*this);
            ListIterator::m_item = ListIterator::m_item->next;

            return it;
        }

        inline bool operator==(list_iterator it)
        {
            return m_item == it.m_item;
        }

        inline bool operator!=(list_iterator it)
        {
            return m_item != it.m_item;
        }

    public:
        explicit ListIterator(ListNode* item)
                :m_item(item)
        {
        }

    protected:
        ListNode* m_item = new ListNode();
    };

public:
    using this_type = MyList;
    using this_type_const = const MyList;
    using this_type_reference = MyList&;
    using this_type_const_reference = const MyList&;
    using this_type_pointer = MyList*;
    using node_type = ListNode;
    using node_pointer = ListNode*;
    using value_type = T;
    using value_pointer = T*;
    using value_const_pointer = const T*;
    using value_reference = T&;
    using value_const_reference = const T&;
    using size_type = size_t;
    using iterator = ListIterator;
    using iterator_reference = ListIterator&;
    using const_iterator = const ListIterator;
    using const_iterator_reference = const ListIterator&;
    using reverse_iterator = ListIterator;
    using riterator_reference = ListIterator&;

public:
    MyList() = default;

    MyList(this_type_const_reference myList)
    {
        if (myList.empty())
        {
            m_begin = nullptr;
            m_end = nullptr;
            m_size = 0;

            return;
        }

        // Copy m_begin
        node_pointer tmp = myList.m_begin;
        m_begin = new node_type;
        m_begin->data = tmp->data;

        // Iterate through dll
        auto curr = m_begin;
        tmp = tmp->next;

        while (tmp)
        {
            curr->next = new node_type;
            curr = curr->next;
            curr->data = tmp->data;
            curr->prev = tmp->prev;

            // Last element found
            if (!tmp->next)
            {
                // Copy m_end
                m_end = new node_type;
                m_end = curr;
            }

            tmp = tmp->next;
        }

        m_size = myList.m_size;
    }

    inline bool operator==(this_type list)
    {
        auto it = iterator(m_begin);
        for (auto inIt = iterator(list.m_begin); inIt != iterator(list.m_end); ++inIt)
        {
            if (*it != *inIt)
            {
                return false;
            }

            ++it;
        }

        return true;
    }

    inline bool operator==(this_type_const list) const
    {
        auto it = iterator(m_begin);
        for (auto inIt = iterator(list.m_begin); inIt != iterator(list.m_end); ++inIt)
        {
            if (*it != *inIt)
            {
                return false;
            }

            ++it;
        }

        return true;
    }

    inline bool operator!=(this_type list)
    {
        return !(*this == list);
    }

    inline bool operator!=(this_type_const list) const
    {
        return !(*this == list);
    }

    void push_front(value_const_reference value)
    {
        auto node = new node_type(value);

        if (empty())
        {
            m_end = node;
            m_begin = node;
        }
        else
        {
            m_begin->prev = node;
            node->next = m_begin;
            m_begin = node;
        }

        m_size++;
    }

    void push_back(value_const_reference value)
    {
        auto node = new node_type(value);

        if (empty())
        {
            m_end = node;
            m_begin = node;
        }
        else
        {
            node->prev = m_end;
            m_end->next = node;
            m_end = node;
        }

        m_size++;
    }

    iterator insert(iterator_reference pos, value_const_reference value)
    {
        auto item = pos.m_item;

        if (m_begin == item)
        {
            push_front(value);
        }
        else if (m_end == item)
        {
            push_back(value);
        }
        else
        {
            auto node = new node_type(value, item);

            item->prev->next = node;
            node->next = item;
            node->prev = item->prev;
            item->prev = node;
        }

        m_size++;

        return pos;
    }

    void remove(value_const_reference value)
    {
        for (auto it = iterator(m_begin); it != iterator(m_end); ++it)
        {
            auto curr = it.m_item;

            if (value == curr->data)
            {
                if (m_begin == curr)
                {
                    m_begin->prev = nullptr;
                    m_begin = m_begin->next;
                }
                else if (m_end == curr)
                {
                    m_end->prev->next = nullptr;
                    m_end = m_end->prev;
                }
                else
                {
                    curr->next->prev = curr->prev;
                    curr->prev->next = curr->next;
                }

                m_size--;
            }
        }
    }

    iterator erase(iterator_reference pos)
    {
        auto item = pos.m_item;

        if (m_begin == item && m_end == item)
        {
            Destroy();
        }
        else if (m_begin == item)
        {
            m_begin = m_begin->next;
        }
        else if (m_end == item)
        {
            m_end = m_end->prev;
        }
        else
        {
            item->prev->prev->next = item;
            item->prev = item->prev->prev;
        }

        m_size--;

        return pos;
    }

    value_type front() const
    {
        return m_begin->data;
    }

    value_type back() const
    {
        return m_end->data;
    }

    [[nodiscard]] bool empty() const
    {
        return m_size == 0;
    }

    [[nodiscard]] size_type size() const
    {
        return m_size;
    }

    ~MyList() noexcept
    {
        Destroy();
    }

    iterator begin()
    {
        return iterator(m_begin);
    }

    iterator end()
    {
        return iterator(m_end->next);
    }

    const_iterator begin() const
    {
        return iterator(m_begin);
    }

    const_iterator end() const
    {
        return iterator(m_end->next);
    }

    reverse_iterator rbegin()
    {
        return iterator(m_end);
    }

    reverse_iterator rend()
    {
        return iterator(m_begin->prev);
    }

private:
    void Destroy()
    {
        node_pointer curr = nullptr;

        while (m_begin)
        {
            curr = m_begin;
            m_begin = m_begin->next;

            delete curr;
        }

        delete m_begin;
    }

private:
    node_pointer m_begin = nullptr;
    node_pointer m_end = nullptr;

    size_type m_size = 0;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, MyList<T>& myList)
{
    std::stringstream ss;
    for (auto element : myList)
    {
        ss << element << " ";
    }

    // Remove extra space
    std::string out = ss.str().substr(0, ss.str().size() - 1);
    os << out;

    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyList<T>& myList)
{
    std::stringstream ss;
    for (auto element : myList)
    {
        ss << element << " ";
    }

    // Remove extra space
    std::string out = ss.str().substr(0, ss.str().size() - 1);
    os << out;

    return os;
}