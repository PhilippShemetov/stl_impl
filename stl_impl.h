
#ifndef __STL_IMPL__
#define __STL_IMPL__

//Имплементация свой библиотеки на основе stl(для обучения и получения опыта)
//Пока что только для контейнеров и вспомогательных классов
namespace stl_impl {

    

    //Имплементация умного указателя(пока что без Deleter и специализации на T[])
    template<typename T>
    class unique_ptr{
    private:
        T* ptr;
    public:
        unique_ptr() noexcept : ptr(nullptr) {}
        unique_ptr(T* new_ptr) noexcept : ptr(new_ptr) {}
        unique_ptr(unique_ptr&& move_ptr) {
            ptr = move_ptr.ptr;
            move_ptr.ptr = nullptr;
        }
        ~unique_ptr(){
            if (get() == nullptr){

            } else {
                delete ptr;
                ptr = nullptr;
            }
            
        }

        unique_ptr& operator=(unique_ptr&& move_ptr){
            ptr = move_ptr.ptr;
            move_ptr.ptr = nullptr;
            return *this;
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
        friend bool operator==(const unique_ptr<T>& ptr1, const unique_ptr<T>& ptr2){
            return *ptr1.get() == *ptr2.get() ? true : false;
        }

        friend bool operator!=(const unique_ptr<T>& ptr1, const unique_ptr<T>& ptr2){
            return *ptr1.get() != *ptr2.get() ? true : false;
        }
        


    };

    //Имплементация односвязного списка
    template <typename T>
    class forward_list {
    private:
        struct node:  {
            unique_ptr<node> pNext;
            T data;
            node(){}
            node(T new_data = T(), unique_ptr<node> new_pNext = nullptr) : data{new_data} , pNext{new_pNext}
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