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
//            if (ptr) {
//                delete ptr;
//            }
//            ptr = move_ptr.ptr;
//            move_ptr.ptr = nullptr;
//            return *this;
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
            unique_ptr<node> pNext;
            T data;

            node() = default;

            explicit node(T new_data = T(), unique_ptr<node> new_pNext = nullptr) : data{new_data}, pNext{new_pNext.get()} {}
        };

        size_t size;
        unique_ptr<node> head;

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
                if(ptr->pNext){
                    ptr = ptr->pNext;
                }

                return *this;
            }
        private:
            node* ptr{nullptr};

        };

        iterator begin(){
            return iterator(head.get());
        }

        forward_list() : head{nullptr} {}

//        forward_list(std::initializer_list<T> init){

//
//        }
        ~forward_list() {
            clear();
        };



        void push_front(T data) {
            unique_ptr<node> temp = make_unique<node>(data);
            if(head) temp->pNext = std::move(head);
            head = std::move(temp);
        }

        void push_back(T data) {

        }

        void clear() {
            while (head) {
                head = std::move(head->pNext);
            }
        }


    };


}


#endif //__STL_IMPL__