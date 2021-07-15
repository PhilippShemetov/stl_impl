// Copyright 2021 Shemetov Philipp

#ifndef __STL_IMPL__
#define __STL_IMPL__

//Имплементация свой библиотеки на основе stl(для обучения и получения опыта)
//Пока что только для контейнеров и вспомогательных классов
namespace stl_impl {

    

    //Имплементация умного указателя(пока что без Deleter и частичной специализации на T[])
    template<typename T>
    class unique_ptr{
    private:
        T* ptr;
    public:
        unique_ptr() noexcept 
        : ptr{nullptr} {}
        unique_ptr(T* new_ptr) noexcept 
        : ptr{new_ptr} {}
        unique_ptr(unique_ptr<T>&& move_ptr)
        : ptr{std::move(move_ptr.ptr)} {
            move_ptr.ptr = nullptr;
        }
        ~unique_ptr(){
            if (get()){
                delete ptr;
                ptr = nullptr;
            }
        }

        unique_ptr<T>& operator=(unique_ptr<T>&& move_ptr){
            if(this == &move_ptr) {
                return *this;
            }
            if(ptr) {
                delete ptr;  
            }
            ptr = move_ptr.ptr;
            move_ptr.ptr = nullptr;
            return *this;
        }
        void reset(T* new_ptr){
            T* old_ptr = ptr;
            ptr = new_ptr;
            if(old_ptr){
                delete old_ptr;
            }
        }
        T* get() const noexcept{
            return ptr;
        }
        T& operator*(){
            return *ptr;
        }
        T* operator->(){
            return ptr;
        }
        T* release() noexcept{
            T* temp_ptr = ptr;
            ptr = nullptr;
            return temp_ptr;
        }
        // friend bool operator==(const unique_ptr<T>& ptr1, const unique_ptr<T>& ptr2){
        //     return *ptr1.get() == *ptr2.get() ? true : false;
        // }

        // friend bool operator!=(const unique_ptr<T>& ptr1, const unique_ptr<T>& ptr2){
        //     return *ptr1.get() != *ptr2.get() ? true : false;
        // }
        


    };

    //Имплементация односвязного списка
    template <typename T>
    class forward_list {
    private:
        struct node {
            unique_ptr<node> pNext;
            T data;
            node(){}
            node(T new_data = T(), unique_ptr<node> new_pNext = nullptr) : data{new_data} , pNext{new_pNext} {}
        };
        unique_ptr<node> head;
    public:
        forward_list(): head{nullptr} {}
        ~forward_list(){
        }
        // clear(){
        //     while(head){
        //         head = std::move(head->get());
        //     }
        // }
    
    
    
    
    
    };






















}





#endif //__STL_IMPL__