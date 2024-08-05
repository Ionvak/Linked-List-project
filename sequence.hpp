#include <iostream>
#include <string>

#ifndef LIST

#define LIST

template<typename info,typename key>

class Sequence{

    private:
        struct Node{
            info value;
            key ID;
            Node* next;

            Node(info input, key label, Node* follow = nullptr) : value(input) , ID(label) , next(follow) {}
        };

        Node* Head;
        Node* Tail;
        int length;


    public:

        class Iterator{
        private:
            Node* pointer;

        public:

            Iterator(Node* input = nullptr) : pointer(input){}

            Iterator& operator++(){
                if(pointer) pointer = pointer->next;
                return *this;
            }

            Iterator operator++(int){
                Iterator temp = *this;
                if(pointer) pointer = pointer->next;
                return temp;
            }

            void jump(const unsigned int& n){
                int counter = 0;
                while(pointer != nullptr && n > counter){
                    (*this)++;
                    counter++;
                }
            }

            Node& operator*() const{
                if(pointer) return *pointer;
                else throw std::runtime_error("Null operator cannot be dereferenced.");
            }

            Node* operator&() const{ return pointer; }

            Iterator& operator=(const Iterator& other){
                pointer = other.pointer;
                return *this;
            }

            Iterator& operator=(const Node*& other){
                pointer = other;
                return *this;
            }

            Iterator(const Iterator& src){ *this = src; }

            bool operator==(const Iterator& other) const{ return pointer == other.pointer; }

            bool operator==(const Node*& other) const{ return pointer == other; }

            bool operator!=(const Iterator& other) const{ return pointer != other.pointer; }

            bool operator!=(const Node*& other) const{ return pointer != other; }

        };



        Sequence() : Head(nullptr) ,Tail(nullptr) ,length(0) {}



        Node* GetFirst() const{ return Head; }



        Node* GetLast() const{ return Tail; }



        unsigned int Size() const{ return length; }



        bool IsEmpty() const{ return Head == nullptr; }



        Node* LookFor(const key& item) const{
            Iterator temp = Head;
            for(int i=0; i<length ;i++){
                if((*temp).ID == item) return &temp;
                temp++;
            }
            return nullptr;
        }



        Node* LookThrough(const key& item, Node* start, Node* stop) const{
            Iterator temp = start;
            while(temp != nullptr && temp != stop){
                if((*temp).ID == item) return &temp;
                temp++;
            }
            return nullptr;
        }



        bool GetInfo(const key& item, info& returned) const{
            Node* temp = this->LookFor(item);
            if(temp != nullptr){
                returned = temp->value;
                return true;
            }
            return false;
        }



        bool GetInfo(const key& item, info& returned, Node* start, Node* stop) const{
            Node* temp = this->LookThrough(item,start,stop);
            if(temp != nullptr){
                returned = temp->value;
                return true;
            }
            return false;
        }



        int Count(const key& item) const{
            int n;
            Iterator temp = Head;
            for(int i=0; i<length ;i++){
                if((*temp).ID == item) n++;
                temp++;
            }
            return n;
        }



        void PushFront(const info& VLnew, const key& IDnew){
            if(length == 0){
                    Head = new Node(VLnew,IDnew);
                    Tail = Head;
                    length++;
            }

            else{
                Tail->next = new Node(VLnew,IDnew);
                Tail = Tail->next;
                length++;
            }
        }



        bool PopFront(){
            Iterator temp = Head;

            if(length == 1){
                Head = Tail = nullptr;
                delete &temp;
                length--;
                return true;
            }

            for(int i=0; i<length ; i++){
                if((*temp).next == Tail){
                    Node* X = Tail;
                    Tail = &temp;
                    temp = X;
                    Tail->next = nullptr;
                    delete &temp;
                    length--;
                    return true;
                }
                temp++;
            }
            return false;

        }



        void PushBack(const info& VLnew, const key& IDnew){
            Head = new Node(VLnew,IDnew,Head);
            if(length==0) Tail = Head;
            length++;
        }



        bool PopBack(){
            if(length>0){
                Node* temp = Head;
                Head = Head->next;
                if(length == 1) Tail = nullptr;
                delete temp;
                length--;
                return true;
            }
            return false;
        }



        bool Remove(const key& item){
            Iterator temp = Head;
            if(Head != nullptr && Head->ID == item){
                this->PopBack();
                return true;
            }

            Iterator prev = Head;
            for(int i=0; i<length ; i++){
                if((*temp).ID == item){
                    if(temp == Tail) Tail = &prev;
                    (*prev).next = (*temp).next;
                    delete &temp;
                    length--;
                    return true;
                }
                if(temp != prev) prev++;
                temp++;
            }

            return false;
        }



        bool Remove(const Iterator& item){
            Iterator temp = Head;
            if(Head != nullptr && item == Head){
                this->PopBack();
                return true;
            }

            Iterator prev = Head;
            for(int i=0; i<length ; i++){
                if(temp == item){
                    if(temp == Tail) Tail = &prev;
                    (*prev).next = (*temp).next;
                    delete &temp;
                    length--;
                    return true;
                }
                if(temp != prev) prev++;
                temp++;
            }

            return false;
        }



        bool Remove(const key& item, Node* start, Node* stop){
            Iterator temp = LookThrough(item,start,stop);
            if(temp != nullptr){
                Remove(temp);
            }
            return false;
        }




        bool Insert(const key& item, const info& VLnew, const key& IDnew){
            Node* temp = this->LookFor(item);
            if(temp != nullptr){
                temp->next = new Node(VLnew,IDnew,temp->next);
                if(temp == Tail) Tail = temp->next;
                length++;
                return true;
            }
            return false;
        }



        bool Insert(const Iterator& item, const info& VLnew, const key& IDnew){
            Iterator temp = Head;
            for(int i=0; i<length ;i++){
                if(temp == item){
                    temp->next = new Node(VLnew,IDnew,temp->next);
                    if(temp == Tail) Tail = temp->next;
                    length++;
                    return true;
                }
                temp++;
            }
            return false;
        }



        bool Insert(const key& item, const info& VLnew, const key& IDnew, Node* start, Node* stop){
            Node* temp = this->LookThrough(item,start,stop);
            if(temp != nullptr){
                this->Insert(temp,VLnew,IDnew);
                return true;
            }
            return false;
        }



        bool Invert(){
            if(length > 1){
                Node* prev = Head;
                Node* curr = Head;
                Iterator after = Head->next;

                for(int i=0; i<length ; i++){
                    curr->next = prev;
                    if(curr != prev) prev = curr;
                    curr = &after;
                    if(&after != nullptr) after++;
                }

                Head->next = nullptr;
                curr = Head;
                Head = Tail;
                Tail = curr;

                return true;
            }
            else return false;
        }



        void Print(){
            Iterator temp = Head;
            std::cout << "->";
            for(int i=0; i<length ; i++){
                std::cout << '[' << (*temp).ID << ',' << (*temp).value << ']' << "->";
                temp++;
            }

        }



        bool Clear(){
            if(this->IsEmpty()) return false;
            while(length) this->PopBack();
            return true;
        }



        ~Sequence(){ this->Clear(); }



        bool operator==(const Sequence& arg) const{
            if(length != arg.length) return false;
            else{
                Iterator temp1 = Head;
                Iterator temp2 = arg.Head;
                for(int i=0; i<length ;i++){
                    if((*temp1).ID != (*temp2).ID || (*temp1).value != (*temp2).value) return false;
                    temp1++;
                    temp2++;
                }
            return true;
            }
        }



        bool operator!=(const Sequence& arg) const{ return !(*this == arg); }



        Sequence& operator=(const Sequence& src){
        this->Clear();
             if(!src.IsEmpty() && *this != src){
                 Iterator temp = src.Head;
                 for(int i=0; i<src.length ;i++){
                    this->PushFront((*temp).value,(*temp).ID);
                    temp++;
                 }
             }
         return *this;
        }



        Sequence operator+(const Sequence& other) const{
            Sequence returned(*this);
            Iterator temp = other.Head;
            while(returned.Size() != (this->Size() + other.Size())){
                returned.PushFront((*temp).value,(*temp).ID);
                temp++;
            }

            return returned;
        }



        Sequence(const Sequence& src) : Head(nullptr) , Tail(nullptr) , length(0) { *this = src; }
};

#endif // LIST
