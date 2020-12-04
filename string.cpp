#include <iostream>
#include <cstring>
class String {
    size_t size = 0;
    size_t capacity = 0;
    char* str = nullptr;
    void memoryCorrect() {
        if (capacity==0) {
            str = new char[2];
            capacity=2;
        }
        if (4*size <= capacity) {
            char* newStr = new char[capacity/2];
            memcpy(newStr,str,size);
            delete [] str;
            str = newStr;
            capacity = capacity/2;
        }
    }
    void memoryDouble() {
        if (size == capacity) {
            char* newStr = new char[capacity*2];
            memcpy(newStr,str,size);
            delete [] str;
            str = newStr;
            capacity = capacity*2;
        }
    }
public:
    String() = default;

    String (const char Char) {
        size =1;
        str = new char[2];
        str[0]=Char;
        capacity=2;
    }

    String (size_t sizet, const char Char = '\0'): size(sizet), capacity(sizet*2), str(new char[capacity]) {
        memset(str,Char,size);
    }

    String (const char* line): size(strlen(line)), capacity(2*strlen(line)), str(new char[capacity]) {
        memcpy(str,line,size);
    }

    String& operator=(String line) {
        swap(line);
        return (*this);
    }

    void swap(String& line) {
        std::swap(size,line.size);
        std::swap(str,line.str);
        std::swap(capacity,line.capacity);
    }

    String (const String& line): String(line.size,'\0') {
        memcpy(str,line.str,line.size);
    }

    friend  bool operator==(const String& left , const String& right);

    // Конструктор не забыть написать

    size_t length() const {
        return size;
    }

    char& operator[](const size_t number)  {
        return str[number];
    }

    const char& operator[](const size_t number) const {
        return str[number];
    }

    char& back() {
        return str[size-1];
    }

    const char& back() const {
        return str[size-1];
    }

    char& front() {
        return str[0];
    }

    const char& front() const {
        return str[0];
    }

    void push_back(const char Char) {
        memoryDouble();
        memoryCorrect();
        str[size] = Char;
        size=size+1;
    }

    void pop_back() {
        str[size-1] = '\0';
        size-=1;
        memoryCorrect();
        memoryDouble();
    }

    String& operator+=(const String line) {
        for (size_t i = 0; i<line.size; ++i) {
            push_back(line.str[i]);
        }
        return (*this);
    }

    String& operator+=(const char Char) {
        push_back(Char);
        return (*this);
    }

    String& operator+=(const char* line) {
        for (size_t i=0; i<strlen(line); ++i) {
            push_back(line[i]);
        }
        return (*this);
    }

    void clear() {
        delete [] str;
        str = nullptr;
        size = 0;
        capacity =0;
    }

    bool empty() {
        if (size==0) {
            return true;
        }
        else return false;
    }

    size_t find(const String& substring) const {
        if (substring.size==0) {
            return 0;
        }
        for (size_t i=0; i<size; ++i) {
            if(str[i]==substring.str[0]) {
                bool result = true;
                for (size_t j = 0; j<substring.size; ++j) {
                    if (i+j<size) {
                        if(str[i+j]!=substring.str[j]) {
                            result=false;
                        }
                    }
                    else result=false;
                }
                if(result==true) return i;
            }
        }
        return size;
    }
    size_t rfind(const String& substring) const {
        long long max=-1;
        if (substring.size==0) {
            return size-1;
        }
        for (size_t i=0; i<size; ++i) {
            if(str[i]==substring.str[0]) {
                bool result = true;
                for (size_t j = 0; j<substring.size; ++j) {
                    if (i+j<size) {
                        if(str[i+j]!=substring.str[j]) {
                            result=false;
                        }
                    }
                    else result=false;
                }
                if (result==true) {
                    if (max == -1) {
                        max=i;
                    }
                    else if ( i > (long long unsigned)max ) {
                        max = i;
                    }
                }
            }
        }
        if (max==-1) {
            return size;
        }
        else {
            return max;
        }
    }
    
    String substr(const size_t start , const size_t count) const  {
        char* copy_CS;
        copy_CS = new char[count];
        for (size_t i = start ; i < start + count ; ++i) {
            copy_CS[i-start] = str[i];
        }
        String copy = copy_CS;
        delete [] copy_CS;
        return copy;
    }

    friend  std::ostream& operator << (std::ostream& os , const String line);
    
    friend std::istream& operator >> (std::istream& in , String& line);

    ~String() {
        delete [] str;
    }
};

bool operator==(const String& left, const String& right) {
    if (left.size != right.size) {
        return false;
    }
    else {
        bool result = true;
        for (size_t i; i<left.size; ++i) {
            if (left.str[i]!=right.str[i]) {
                result = false;
            }
        }
        return result;
    }
}

String operator+ ( const String& left , const String& right ) {
    String copy = left;
    copy+=right;
    return copy;
}
String operator+ (const String& left , const char Char ) {
    String copy = left;
    String right = Char;
    copy+=right;
    return copy;
}
String operator+ ( const char Char , const String& right ) {
    String copy = Char;
    copy+=right;
    return copy;
}
String operator+ ( const char* left , const String& right) {
    String copy = left;
    copy+=right;
    return copy;
}
String operator+ ( const String& left , const char* C_right) {
    String copy = left;
    String right = C_right;
    copy+=right;
    return copy;
}

std::ostream& operator << (std::ostream& ou , const String line) {
    for (long long unsigned i = 0 ; i < line.size ; ++i ) {
        ou << line.str[i];
    }
    return ou;
}

std::istream& operator >> (std::istream& in , String& line) {
    line.clear();
    while (true) {
        long long symbol;
        symbol = in.get();
        if ( symbol==-1 ) {
            break;
        }
        if ( symbol==32 ) {
            break;
        }
        if ( symbol==9 ) {
            break;
        }
        if ( symbol==10 ) {
            break;
        }
        line.push_back(symbol);
    }
    return in;
}


