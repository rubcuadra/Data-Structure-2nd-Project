
template <class T>
class DoubleNode
{
    private:
        T data;
        DoubleNode * next = nullptr;
        DoubleNode * previous = nullptr;

    public:
        // Constructors
        DoubleNode () {};
        DoubleNode (T _data) { data = _data; }
        // Destructor
        ~DoubleNode ();

        // Access methods
        T getData();
        void setData(T _item);
        DoubleNode * getNext();
        void setNext(DoubleNode* _pointer);
        DoubleNode * getPrevious();
        void setPrevious(DoubleNode* _pointer);
};

template <class T>
T DoubleNode<T>::getData()
{
    return this->data;
}

template <class T>
void DoubleNode<T>::setData(T new_data)
{
    this->data = new_data;
}

template <class T>
DoubleNode<T> * DoubleNode<T>::getNext()
{
    return this->next;
}

template <class T>
void DoubleNode<T>::setNext(DoubleNode* next_node)
{
    this->next = next_node;
}
template <class T>
DoubleNode<T> * DoubleNode<T>::getPrevious()
{
    return this->previous;
}

template <class T>
void DoubleNode<T>::setPrevious(DoubleNode* previous_node)
{
    this->previous = previous_node;
}

template <class T>
DoubleNode<T>::~DoubleNode()
{
    data.~T();
    next = nullptr;
    previous = nullptr;
}
