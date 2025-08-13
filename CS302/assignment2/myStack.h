
template <class Type>
class myStack{
public :
    myStack ();
    myStack(const myStack<Type>&);
    const myStack <Type>& operator=(const myStack <Type>&);
    ~ myStack ();
    void push (const Type &);
    void pop ();
    Type top () const ;
    bool isEmpty () const ;
private :
    struct node
    {
    Type item;
    node * next;
    };
    node * topOfMyStack;
};

template <class Type>
myStack<Type>::myStack(){
    topOfMyStack = nullptr;                     //default constructor
}

template <class Type>
myStack<Type>::myStack(const myStack<Type>& copy){
    if(copy.isEmpty()){                        //check if copy is empty
        this->topOfMyStack = nullptr;
        return;
    }
    node *temp, *read;
    temp = new node;
    this->topOfMyStack = temp;                  //temp points to this
    read = copy.topOfMyStack;                   //read points to the stack to be copied
    temp->item = read->item;
    read = read->next;
    while(read != nullptr){                     //while the read pointer still has data
        temp->next = new node;                  //make a new node for this
        temp = temp->next;
        temp->next = nullptr;
        temp->item = read->item;
        read = read->next;

    }
    return;
}

template <class Type>
const myStack<Type>& myStack<Type>::operator=(const myStack<Type>& rhs){
    while(!this->isEmpty())                     //deallocate old stack
        this->pop();
    if(rhs.isEmpty()){                          //if rhs is empty
        this->topOfMyStack = nullptr;
        return *this;
    }
    node *temp, *read;
    temp = new node;
    this->topOfMyStack = temp;                  //temp points to this
    read = rhs.topOfMyStack;                    //read points to the stack to be copied
    temp->item = read->item;
    read = read->next;
    while(read != nullptr){                     //while the read pointer still has data
        temp->next = new node;                  //make a new node for this
        temp = temp->next;
        temp->next = nullptr;
        temp->item = read->item;
        read = read->next;
    }
    return *this;
}

template <class Type>
myStack<Type>::~myStack(){
    while(!this->isEmpty())                     //pop through the stack
        this->pop();
}

template <class Type>
void myStack<Type>::push(const Type& insert){
    node *temp;
    temp = new node;                            //make a new node
    temp->item = insert;
    temp->next = topOfMyStack;
    topOfMyStack = temp;                        //make it top of stack
    return;
}

template <class Type>
void myStack<Type>::pop(){
    if(topOfMyStack==nullptr)                   //if empty
        return;
    node *temp;
    temp = topOfMyStack;
    topOfMyStack = topOfMyStack->next;
    delete temp;
    return;
}

template <class Type>
Type myStack<Type>::top() const{
    return topOfMyStack->item;                  //retruns item of topofmystack
}

template <class Type>
bool myStack<Type>::isEmpty() const{
    if(topOfMyStack==nullptr)
        return true;
    return false;
}