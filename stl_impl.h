
#ifndef __STL_IMPL__
#define __STL_IMPL__


namespace stl_impl {

    template<typename T>
    class unique_ptr{
    private:
        T* ptr;
    public:
        unique_ptr() noexcept {}
        unique_ptr(T new_ptr) noexcept:
        ptr(new_ptr) {}
        unique_ptr(unique_ptr&& move_ptr){

        }
        ~unique_ptr(){
            delete ptr;
        }
        T get() const noexcept{
            return ptr;
        }
        T& operator*(){
            return *ptr;
        }
        T* operator->(){
            return ptr;
        }


    };

    //Имплементация односвязного списка
    template <typename T>
    class forward_list {
    private:
        struct node:  {
            node* pNext;
            T data;
            node(){}
            node(T data = T(), pNext = nullptr)
        };
        node* head;
    public:
        forward_list(): head(nullptr) {}
        ~forward_list(){
            
        }
        clear(){
            while(head){

            }
        }
    
    
    
    
    
    };






















}





#endif //__STL_IMPL__