namespace MaxCode {

template <class T>
class Queue {
private:
  struct node {
    T key;
    struct node* next;
  };
  int numNodes;
  struct node *head, *z;
public:
  void push(T v);
  T pop();
  int empty();
  int size();
  Queue();
  ~Queue();
};

template <class T>
Queue<T>::Queue()
{
  head = new node;
  z = new node;
  head->next = z;
  z->next = head;
  numNodes = 0;
}

template <class T>
Queue<T>::~Queue()
{
  struct node *t = head;
  while (t != z)
  {
   head = t;
   t = t->next;
   delete head;
  }
  delete z;
}

template <class T>
void Queue<T>::push(T v)
{
 struct node *t = new node;
 t->next = head->next;
 t->key = v;
 head->next = t;
 numNodes++;
}

template <class T>
T Queue<T>::pop()
{
 T x;
 struct node *d, *t = head;
 while (t != z)
 {
   if(t->next->next == z)
    { x = t->next->key; break; }

   t = t->next; 
 }
 d = t->next;
 t->next = z;
 delete d;
 numNodes--;
 return x;
}

template <class T>
int Queue<T>::empty()
{
 return head->next == z;
}
template <class T>
int Queue<T>::size()
{
 return numNodes;
}
};
