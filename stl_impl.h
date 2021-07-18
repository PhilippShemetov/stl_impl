// Copyright 2021 Shemetov Philipp

#ifndef __STL_IMPL__
#define __STL_IMPL__

#include <utility>
#include <memory>

//Имплементация свой библиотеки на основе stl(для обучения и получения опыта)
//TO DO...
// -Односвязный список и тесты
// -Двусвязный список и тесты
// -Статический массив и тесты
// -Динамический массив и тесты
// -Стэк и тесты
// -Очередь и тесты
// ...
//Пока что только для контейнеров и вспомогательных классов
namespace stl_impl {

    //Имплементация умного указателя(пока что без Deleter и частичной специализации на T[])
    template<typename T>
    class unique_ptr {
    private:
        T* ptr;
    public:
        unique_ptr() noexcept
                : ptr{nullptr} {

        }

        unique_ptr(std::nullptr_t _ptr) noexcept
                : ptr{_ptr} {}


        explicit unique_ptr(T* new_ptr) noexcept
                : ptr{new_ptr} {

        }

        unique_ptr(const unique_ptr&) = delete;

        unique_ptr(unique_ptr &&move_ptr) noexcept
                : ptr{std::move(move_ptr.ptr)} {
            move_ptr.ptr = nullptr;
        }

        ~unique_ptr() {
            if (get()) {
                delete ptr;
                ptr = nullptr;
            }
        }


        unique_ptr& operator=(const unique_ptr&) = delete;

        unique_ptr &operator=(unique_ptr &&move_ptr) noexcept {
            if (this == &move_ptr) {
                return *this;
            }
            ptr = move_ptr.ptr;
            move_ptr.ptr = nullptr;
            return *this;
        }

        void reset(T *new_ptr) {
            T *old_ptr = ptr;
            ptr = new_ptr;
            if (old_ptr) {
                delete old_ptr;
            }
        }

        T* get() const noexcept {
            return ptr;
        }

        T& operator*() {
            return *ptr;
        }

        T* operator->() const {
            return ptr;
        }

        T* release() noexcept {
            T *temp_ptr = ptr;
            ptr = nullptr;
            return temp_ptr;
        }

        explicit operator bool() const noexcept {
            return get() != nullptr;
        }

        friend bool operator==(const unique_ptr &ptr1, const unique_ptr &ptr2) {
            return ptr1.get() == ptr2.get();
        }

        friend bool operator!=(const unique_ptr &ptr1, const unique_ptr &ptr2) {
            return ptr1.get() != ptr2.get();
        }


    };

    template<typename T, typename... Args>
    typename std::enable_if<!std::is_array<T>::value, unique_ptr<T>>::type make_unique(Args&&... args) {
        return unique_ptr<T>(new T(std::forward<Args>(args)...));
    };

    //Имплементация односвязного списка
    template<typename T>
    class forward_list {
    protected:
        struct node {
            node* pNext;
            T data;

            node() = default;

            explicit node(T new_data = T(), node* new_pNext = nullptr) : data{new_data}, pNext{new_pNext} {}
        };

        size_t size;
        node* head;

    public:

        class iterator{
        public:
            using value_type = T;
            using reference = T&;
            using pointer = T*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            iterator() = default;

            ~iterator() = default;

            explicit iterator(node* _ptr){
                ptr = _ptr;
            }

            iterator(const iterator& it)
                : ptr{it.ptr} {

            }

            iterator& operator=(const iterator& it){
                ptr = it.ptr;
                return *this;
            }

            value_type operator*() const {
                return ptr->data;
            }

            pointer operator->() const {
                return ptr;
            }

            iterator& operator++(){

                ptr = ptr->pNext;

                return *this;
            }

            iterator operator++(int){
                iterator copy{*this};
                ptr = ptr->pNext;

                return copy;
            }
            friend bool operator==(const iterator& lhs, const iterator& rhs)
            {
                return lhs._ptr == rhs._ptr;
            }
            friend bool operator!=(const iterator& lhs, const iterator& rhs)
            {
                return lhs.ptr != rhs.ptr;
            }
            friend bool operator<(const iterator& lhs, const iterator& rhs) {
                return lhs._ptr < rhs._ptr;
            }
        private:
            node* ptr{nullptr};

        };

        iterator begin() const {
            return iterator(head);
        }

        iterator end() const{
            node* temp = head;
            while(temp){
                temp = temp->pNext;
            }
            return iterator(temp);
        }

        forward_list() : head{nullptr} {}

//        forward_list(std::initializer_list<T> init){

//
//        }
        ~forward_list() {
            clear();
        };

        void push_front(T data) {

            if(head == nullptr)
                head = new node(data);
            else{
                head = new node(data,head);
            }


        }

        void push_back(T data) {
            if(head == nullptr){
                head = new node(data);
            } else {
                node* temp = head;
                while(temp->pNext){
                    temp = temp->pNext;
                }
                temp->pNext = new node(data);
            }
        }

        void clear() {
            while (head) {
                node* temp = head;
                head = head->pNext;
                delete temp;
            }
        }


    };


}


#endif //__STL_IMPL__