#ifndef HW5_MTM_ARRAY_H
#define HW5_MTM_ARRAY_H

#include <utility>
#include <stdexcept>


using std::out_of_range

template <class T, int SIZE>
class Array {
    T* data;
public:
    // TODO: Need to complete interface of iterator classes (x++,++x, ->, operator==, operator!=), as well
    // as that of array itself (operator [], operator [] const, ctor, copy ctor, dtor, operator=),
    // and implement everything.

    explicit Array();     //לבדוק אם צריך להשאיר את האקספליסיט או לא
    Array(const Array& array);
    ~Array();
    Array& operator=(const Array& a);
    T& operator[](int index);
    const T& operator[](int index) const;


class iterator {
    Array *array;
    int index;
    iterator(Array* array, int index);

    friend class Array;

public:
    T &operator*();
    iterator &operator++();
    iterator operator++(int);
    bool operator==(const iterator &iterator) const;
    bool operator!=(const iterator &iterator) const;
    iterator(const iterator &) = default;     //  check if we need default
    iterator &operator=(const iterator &) = default; //  check if we need default
    T * operator->();

};


    class const_iterator {
        const Array* array;
        int index;
        const_iterator(const Array* array, int index);
        friend class Array;

    public:
        const_iterator& operator++();
        const_iterator operator++(int);
        bool operator==(const const_iterator& const_iterator) const;
        bool operator!=(const const_iterator& const_iterator) const;
        const_iterator(const const_iterator&) = default;
        const_iterator& operator=(const const_iterator&) = default;
        const T* operator->() const;
        T const& operator*();
    };

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
};
//array
/**
 * the constructor function of Array
 * @tparam T
 * @tparam SIZE
 *return a new Array;
*/
template <class T, int SIZE>
Array<T,SIZE>::Array() : data(new T[SIZE]){
}

/**
 * the copy constructor of array
 * @tparam T
 * @tparam SIZE
 * @param array
 */
template <class T, int SIZE>
Array<T,SIZE>:: Array(const Array& array) : data(new T[SIZE]) {
    for (Array<T, SIZE>::iterator it = array.begin(); it != array.end(); ++it) {
        data[it.index] = array.data[it.index];
    }
}

/**
 * destructor of the array
 * @tparam T
 * @tparam SIZE
 */
template <class T, int SIZE>
Array<T,SIZE>::~Array() {
    delete[] data;
}

/**
 * the = operator if array
 * @tparam T
 * @tparam SIZE
 * @param array
 * @return array with the parapm of array
 */
template <class T, int SIZE>
Array& Array::operator=(const Array& array) {
    if (this == &array) {
        return *this;
    }
    delete[] data;
    data = new T[SIZE];

    for(Array<T,SIZE>::iterator it=array.begin(); it!=array.end();++it){
        data[it.index] = array.data[it.index];
    }
    return *this;
}

/**
 * the [] opertor to array
 * @tparam T
 * @tparam SIZE
 * @param index
 * @return the data in place index
 */
template <class T, int SIZE>
T& Array::operator[](int index) {

    if(index< 0|| index>SIZE)
        throw std::out_of_range;            //////check if this is ok
    return data[index];
}

/**
 * the [] opertor to array
 * @tparam T
 * @tparam SIZE
 * @param index
 * @return the data in place index
 */
template <class T, int SIZE>
const T& Array::operator[](int index) const{
    if(index< 0||index>SIZE)
        throw std::out_of_range;
    return data[index];
}



//the function of the regular iterator


template<class T,int SIZE>
Array<T,SIZE>::iterator::iterator(Array<T,SIZE>* array, int index) :
        array(array), index(index) {
}


template<class T,int SIZE>
T& Array<T,SIZE>::iterator:: operator*(){
if(index<0 || index>SIZE)
    throw out_of_range;
return array->data[this->index];
};


/**
 * for the  regular iterator
 * make the iterator: ++iterator
 * @tparam SIZE - the size of the array
 * @return a iterator from type const_iterator
 */
template<class T,int SIZE>
iterator& Array<T,SIZE>::iterator::operator++(){
    ++index;
    return *this;
};


/**
 * for the  regular iterator
 * make to the iterator: iterator++
 * @tparam SIZE - the size of the array
 * @return a iterator from type iterator
 */
template<class T,int SIZE>
iterator Array<T,SIZE>::iterator::operator++(int){
    iterator result = *this;
    ++*this;
    return result;
};



/**
 * for the regular iterator
 * @tparam T -return pointer of the object in the index if the iterator
 * @tparam SIZE - the size of the array
 */
template<class T,int SIZE>
T *  Array<T,SIZE>::iterator:: operator->(){
    if(index<0 || index>SIZE)
        throw out_of_range;
    return &(array->data[index]);
};


/**
 * the opeator == to the iterator
 * @tparam T
 * @tparam SIZE
 * @param iterator
 * @return true if the 2 iterators eqal and false else
 */
template <class T, int SIZE>
bool Array<T,SIZE>::iterator::operator==(const iterator &iterator) const{
    return index == iterator.index;
}

/**
 * the opeator != to the iterator
 * @tparam T
 * @tparam SIZE
 * @param iterator
 * @return true if the 2 iterators different and false else
 */
template <class T, int SIZE>
bool Array<T,SIZE>::iterator::operator!=(const iterator& iterator) const {
    return !(*this == iterator);
}



//the function of the const_iterator

template<class T,int SIZE>
Array<T,SIZE>::const_iterator::const_iterator(const Array<T,SIZE>* array,
                                              int index) :
        array(array), index(index) {
}



template<class T,int SIZE>
T const& Array<T,SIZE>::const_iterator:: operator*(){
    if(index<0 || index>SIZE)
        throw out_of_range;
    return array->data[this->index];
};

/**
 * for the const_iterator
 * make the iterator: ++iterator
 * @tparam SIZE - the size of the array
 * @return a iterator from type const_iterator
 */
template<class T,int SIZE>
const_iterator& Array<T,SIZE>::const_iterator::operator++(){
    ++index;
    return *this;
};

/**
 * for the const_iterator
 * make to the iterator: iterator++
 * @tparam SIZE - the size of the array
 * @return a iterator from type const_iterator
 */
template<class T,int SIZE>
const_iterator Array<T,SIZE>::const_iterator::operator++(int){
    const_iterator result = *this;
    ++*this;
    return result;
};


/**
 * for const_iterator
 * @tparam T -return pointer of the object in the index if the iterator
 * @tparam SIZE - the size of the array
 */
template<class T,int SIZE>
const T* Array<T,SIZE>::const_iterator::operator->() const{
    if(index<0 || index>SIZE)
        throw out_of_range;
    return &(array->data[index]);
};


/**
 * the opeator == to the iterator
 * @tparam T
 * @tparam SIZE
 * @param const_iterator
 * @return true if the 2 iterator eqal and false else
 */
template <class T, int SIZE>
bool Array<T,SIZE>::const_iterator::operator==(const const_iterator &const_iterator) const{
    return index == const_iterator.index;
}
/**
 * the opeator != to the iterator
 * @tparam T
 * @tparam SIZE
 * @param const_iterator
 * @return true if the 2 iterators different and false else
 */
template <class T, int SIZE>
bool Array<T,SIZE>::const_iterator::operator!=(const const_iterator& const_iterator) const {
    return !(*this == const_iterator);
}



#endif //HW5_MTM_ARRAY_H
