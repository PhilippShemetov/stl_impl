// Copyright 2021 Shemetov Philipp

#ifndef __STL_IMPL__
#define __STL_IMPL__

#include <utility>

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

    template <typename T>
    class forward_list;
    //Имплементация итератора
    template<typename T>
    struct iterator {

        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;


        iterator() = default;

        iterator(const iterator &it) : ptr{it.ptr} {}

        iterator& operator=(const iterator & it) {
            ptr = it.ptr;
            return *this;
        }

        ~iterator() {

        }

        reference operator*() const {
            return *ptr;
        }

        reference operator++(){
            ++ptr;

            return *this;
        };

    protected:
        iterator(T* value) : ptr{value} {}

        friend class forward_list<T>;

        pointer ptr{nullptr};
    };

    template <typename T>
    struct input_iterator : public virtual iterator<T>{

        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        iterator<T> operator++(int){
            iterator<T> tmp = *this;
            ++this->ptr;
            return tmp;
        }
        value_type operator*() const {
            return *this->ptr;
        }
        pointer operator->() const {
            return this->ptr;
        };
        friend bool operator==(const iterator<T>& it_first, const iterator<T>& it_second){
            return it_first.ptr == it_second.ptr;
        }
        friend bool operator!=(const iterator<T>& it_first, const iterator<T>& it_second){
            return it_first.ptr != it_second.ptr;
        }


    };

    template <typename T>
    struct output_iterator : public virtual iterator<T>{
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::output_iterator_tag;

        reference operator*() const{
            return *this->ptr;
        }
    };

    template <typename T>
    struct forward_iterator : output_iterator<T>,input_iterator<T>{
        forward_iterator(){

        }
    };


    //Имплементация умного указателя(пока что без Deleter и частичной специализации на T[])
    template<typename T>
    class unique_ptr {
    private:
        T *ptr;
    public:
        unique_ptr() noexcept
                : ptr{nullptr} {}

        explicit unique_ptr(T *new_ptr) noexcept
                : ptr{new_ptr} {}

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

        unique_ptr &operator=(unique_ptr &&move_ptr) noexcept {
            if (this == &move_ptr) {
                return *this;
            }
            if (ptr) {
                delete ptr;
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
    std::enable_if<!std::is_array<T>::value, unique_ptr<T>> make_unique(Args... args) {
        return unique_ptr<T>(new T(std::forward<Args>(args)...));
    };

    //Имплементация односвязного списка
    template<typename T>
    class forward_list {
    public:

        forward_iterator<T> begin() const{
            return forward_iterator<T>();
        }
        forward_iterator<T> end() const{

        }

        forward_list() : head{nullptr} {}
//        forward_list(std::initializer_list<T> init){

//
//        }
        ~forward_list() {
            clear();
        };

        void push_front(T data) {
            if (head == nullptr) {
                head = make_unique<node>(data, nullptr);
            }
        }

        void push_back(T data) {

        }

        void clear() {
            while (head) {
                head = std::move(head->pNext);
            }
        }

    private:
        struct node {
            unique_ptr<node> pNext;
            T data;

            node() = default;

            explicit node(T new_data = T(), unique_ptr<node> new_pNext = nullptr) : data{new_data}, pNext{new_pNext} {}
        };

        unique_ptr<node> head;


    };


}


#endif //__STL_IMPL__