#include <iostream>
#include <string>

template <typename Object>
class Deque {
public:
    // ИТЕРАТОР
    template <bool Check>
    struct iterator_in: public std::iterator<std::random_access_iterator_tag, Object> {
    public:
        // Ссылка, указатель на блоки, указатель на массив указателей, индекс
        using type_point = typename::std::conditional<Check, const Object*, Object*>::type;
        using type_blocks = typename::std::conditional<Check, const Object**, Object**>::type;
        using type_size = typename::std::conditional<Check, const long long, long long>::type;
        using type_index = typename::std::conditional<Check, const long long, long long>::type;
        using type_link = typename::std::conditional<Check, const Object&, Object&>::type;

        type_point object_point;
        type_blocks array;
        type_size block_size;
        type_index index;

    public:
        iterator_in(Object** array_c, Object* object_point_c, type_size block_size_c, type_index index_c):block_size(block_size_c),index(index_c) {
            object_point = object_point_c;
            array = const_cast<type_blocks>(array_c);

        }

        // РАЗЫМЕНОВЫВАНИЕ и ОПЕРАТОР ->
        type_link operator*() const {
            return (*array)[index];
        }
        type_point operator->() const {
            return &((*array)[index]);
        }

        //СЛОЖЕНИЕ И ВЫЧИТАНИЕ С ЦЕЛЫМИ ЧИСЛАМИ (СОСТАВНОЕ)
        iterator_in& operator+=(const long long value) {
            long long enter = (value + index) / block_size;
            array += enter;
            object_point = *array;
            object_point += (value + index) % block_size;
            index = (value + index) % block_size;
            return *this;
        }

        iterator_in& operator-=(const long long value) {
            long long enter = (value - index) / block_size + bool((value - index) % block_size);
            array -= enter;
            index +=  enter * block_size - value;
            array += index / block_size;
            index = index % block_size;
            object_point = (*array) + index;
            return *this;
        }

        // ИНКРЕМЕНТ и ДЕКРЕМЕНТ
        iterator_in& operator++() {
            *this+=1;
            return *this;
        }
        iterator_in& operator++(int) {
            iterator_in copy = *this;
            copy+=1;
            return copy;
        }
        iterator_in& operator--() {
            *this-=1;
            return *this;
        }
        iterator_in& operator--(int) {
            iterator_in copy = *this;
            copy+=-1;
            return copy;
        }

        // СЛОЖЕНИЕ И ВЫЧИТАНИЕ С ЦЕЛЫМИ ЧИСЛАМИ (ОБЫЧНЫЕ)
        iterator_in operator+(const int n) const {
            iterator_in copy = *this;
            copy += n;
            return copy;
        }
        iterator_in <false> operator-(const int n) const {
            iterator_in <false> copy(const_cast<Object**>(array), const_cast<Object*>(object_point), block_size, index);
            copy -= n;
            return copy;
        }

        // ВЗЯТИЕ РАЗНОСТИ ДВУХ ИТЕРАТОРОВ
        int operator-(const iterator_in& another) const {
            int answer = index - another.index;
            answer += (array) - (another.array);
            return answer;
        }


        // BOOL функции
        bool operator==(const iterator_in& another) const {
            return (object_point == another.object_point);

        }

        bool operator!=(const iterator_in& another) const {
            return !(*this == another);
        }

        bool operator>(const iterator_in& another) const {
            if (*array > *(another.array)) return true;
            if (index > another.index) return true;
            return false;
        }

        bool operator>=(const iterator_in& another) const {
            return (*this > another || *this == another);
        }

        bool operator<(const iterator_in& another) const {
            return !(*this >= another);
        }

        bool operator<=(const iterator_in& another) const {
            return (*this < another || *this == another);
        }

    };

    using iterator = iterator_in <false>;
    using const_iterator = iterator_in <true>;
    // BEGIN, END, CEND, CBEGIN
    iterator begin() {
        size_t index_first = front.first + (front.second + 1) / block_size;
        size_t index_second = (front.second + 1) % block_size;
        return iterator(deque + index_first, &deque[index_first][index_second], block_size, index_second);
    }

    iterator end() {
        return iterator(deque + back.first, &deque[back.first][back.second], block_size, back.second);
    }

    const_iterator begin() const {
        size_t index_first = front.first + (front.second + 1) / block_size;
        size_t index_second = (front.second + 1) % block_size;
        return const_iterator (deque + index_first, &deque[index_first][index_second], block_size, index_second);
    }

    const_iterator end() const {
        return const_iterator (deque + back.first, &deque[back.first][back.second], block_size, back.second);
    }

    const_iterator cbegin() const {
        size_t index_first = front.first + (front.second + 1) / block_size;
        size_t index_second = (front.second + 1) % block_size;
        return const_iterator (deque + index_first, &deque[index_first][index_second], block_size, index_second);
    }

    const_iterator cend() const {
        return const_iterator (deque + back.first, &deque[back.first][back.second], block_size, back.second);
    }

    // КОНСТРУКТОРЫ и ОПЕРАТОРЫ ПРИСВАИВАНИЯ
    Deque<Object>() {
        capacity = 0;
        my_size = 0;
        front = std::make_pair(0,0);
        back = std::make_pair(0,1);
    }
    Deque<Object>(const int& size_copy) {
        size_t blocks_number = size_copy / block_size + size_t(bool(size_copy % block_size));
        deque = new Object* [blocks_number + 2];
        for (size_t i = 0; i < blocks_number + 2; ++i) {
            deque[i] = reinterpret_cast<Object*>(new int8_t[block_size * sizeof(Object)]);
        }

        my_size = size_copy;
        capacity = (blocks_number + 2) * (block_size);

        front.first = 0;
        front.second = block_size - 1;

        back.first = size_copy / block_size + 1;
        back.second = size_copy % block_size;
    }
    Deque<Object>(const Deque <Object>& deque_copy) {
        Object** old_deque = deque;
        deque = new Object* [deque_copy.capacity / deque_copy.block_size];
        size_t i = 0;
        try {
            for (; i < deque_copy.capacity / deque_copy.block_size; ++i) {
                deque[i] =  reinterpret_cast<Object*>(new int8_t[block_size * sizeof (Object)]);
                std::uninitialized_copy(deque_copy.deque[i], deque_copy.deque[i] + block_size, deque[i]);
            }
        } catch (...) {
            for (size_t j = 0; j < i; ++j) {
                delete[] reinterpret_cast<int8_t*>(deque[j]);
            }
            delete [] deque;
            deque = old_deque;
            //throw;
            //for (int i = 0; i < capacity; ++i) {
            //  delete[] reinterpret_cast<int8_t*>(old_deque[i]);
            //}
            //delete []  old_deque;
            throw;
        }

        for (size_t i = 0; i < capacity; ++i) {
            delete[] reinterpret_cast<int8_t*>(old_deque[i]);
        }
        /*
        delete []  old_deque;
        */
        my_size = deque_copy.my_size;
        capacity = deque_copy.capacity;
        front = deque_copy.front;
        back = deque_copy.back;
    }
    Deque<Object>(const size_t& size_copy, const Object& object):Deque(size_copy){
        my_size = size_copy;
        size_t ind_x = front.first;
        size_t ind_y = front.second + 1;
        if (ind_y == block_size) {
            ind_x++;
            ind_y = 0;
        }
        try {
            for (size_t i = 0; i < size_copy; ++i) {
                new (deque[ind_x] + ind_y) Object(object);
                ind_y++;
                if (ind_y == block_size) {
                    ind_x++;
                    ind_y = 0;
                }
            }
        } catch (...) {
            throw;
        }
    }
    Deque<Object>& operator=(const Deque<Object>& deque_copy) {
        Deque<Object> copy = deque_copy;
        swap(copy);
        return *this;
    }

    // МЕТОДЫ ПРОВЕРКИ
    size_t size() const {
        return my_size;
    }
    Object& operator[](const size_t& index) {
        size_t index_first = front.first + (front.second + 1 + index) / block_size;
        size_t index_second = (front.second + 1 + index) % block_size;
        return deque[index_first][index_second];
    }
    Object& at(const size_t& index) {
        if (index >= my_size) {
            throw (std::out_of_range(""));
        }
        else {
            return (*this)[index];
        }
    }
    const Object& operator[](const size_t& index) const {
        size_t index_first = front.first + (front.second + 1 + index) / block_size;
        size_t index_second = (front.second + 1 + index) % block_size;
        return deque[index_first][index_second];
    }
    const Object& at(const size_t& index) const {
        if (index >= my_size) {
            throw (std::out_of_range(""));
        }
        else {
            return (*this)[index];
        }
    }

    // МЕТОДЫ ДОБАВЛЕНИЯ/УДАЛЕНИЯ
    void push_back(const Object& object) {
        if (capacity == 0) fix_capacity();
        //Object x = Object(object);
        //new (deque[back.first] + back.second) Object(object);
        new (deque[back.first] + back.second) Object(object);
        back.second++;
        if ((size_t)back.second == block_size) {
            back.second = 0;
            back.first += 1;
            if ((size_t)back.first == (capacity / block_size)){
                fix_capacity();
            }
        }
        my_size++;
    }
    void push_front(const Object& object) {
        if (capacity == 0) fix_capacity();
        new (deque[front.first] + front.second) Object(object);
        front.second--;
        if (front.second == -1) {
            front.second = block_size - 1;
            front.first -= 1;
            while (front.first < 0) {
                fix_capacity();
            }
        }
        my_size++;
    }
    void pop_back() {
        back.second--;
        if (back.second == -1) {
            back.second = block_size - 1;
            back.first--;
        }
        my_size--;
    }
    void pop_front() {
        front.second++;
        if ((size_t)front.second == block_size) {
            front.second = 0;
            front.first++;
        }
        my_size--;
    }
    void print() {
        std::cout << "Begin " << front.first << " " << front.second << '\n';
        std::cout << "End " << back.first << " " << back.second << '\n';
        for (int i = 0; i < capacity / block_size; ++i) {
            for (int j = 0; j < block_size; ++j) {
                std::cout << deque[i][j] << " ";
            }
            std::cout << '\n';
        }
    }
    // ВСТАВКА/УДАЛЕНИЕ В DEQUE по ИТЕРАТОРУ
    void insert(iterator it, const Object& value) {
        Object cur_insert_value = value;
        while (it != this->end()) {
            Object buffer = *it;
            *it = cur_insert_value;
            cur_insert_value = buffer;
            ++it;
        }
        (*this).push_back(cur_insert_value);
    }

    void erase(iterator it) {
        while (it + 1 != this->end()) {
            *it = *(it + 1);
            ++it;
        }
        (*this).pop_back();
    }


private:
    const size_t block_size = 200;
    Object** deque;
    size_t my_size = 0;
    size_t capacity = 0;
    std::pair <int, int> front;
    std::pair <int, int> back;
    void fix_capacity() {
        size_t blocks_number = capacity / block_size;
        size_t new_blocks_number = blocks_number * 2;
        if (new_blocks_number == 0) new_blocks_number = 1;
        Object **new_deque = new Object *[new_blocks_number];
        for (size_t i = 0; i < new_blocks_number; ++i) {
            new_deque[i] = reinterpret_cast<Object *>(new int8_t[block_size * sizeof(Object)]);
        }

        size_t new_index = new_blocks_number / 3;
        size_t save_new_index = new_index;
        Object **old_deque = deque;
        //delete [] deque;
        for (size_t i = 0; i < blocks_number; ++i) {
            new_deque[new_index] = old_deque[i];
            new_index++;
        }

        deque = new_deque;
        back.first += save_new_index;
        front.first += save_new_index;
        capacity = new_blocks_number * block_size;
    }

    void swap(Deque<Object>& copy) {
        std::swap(my_size, copy.my_size);
        std::swap(capacity, copy.capacity);
        std::swap(front, copy.front);
        std::swap(back, copy.back);
        std::swap(deque, copy.deque);
    }

};

