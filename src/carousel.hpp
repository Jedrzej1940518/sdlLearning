#include <array>

template <typename T, size_t SIZE>
class Carousel
{
public:
    T pop()
    {
        T elem = last();
        --numElems;
        currentIndex = currentIndex == 0 ? numElems - 1 : currentIndex - 1;
        return elem;
    }
    void clear()
    {
        numElems = 0;
        currentIndex = 0;
    }
    void addElem(T elem)
    {
        currentIndex = (currentIndex + 1) % SIZE;
        arr[currentIndex] = elem;
        numElems = numElems < SIZE ? numElems + 1 : numElems;
    }

    T &getElem()
    {
        T &elem = arr[currentIndex];
        currentIndex = (currentIndex + 1) % numElems;
        return elem;
    }
    T &getElemReverse()
    {
        T &elem = arr[currentIndex];
        currentIndex = currentIndex == 0 ? numElems - 1 : currentIndex - 1;
        return elem;
    }

    T &last()
    {
        return arr[currentIndex];
    }
    bool empty()
    {
        return numElems == 0;
    }

    size_t size()
    {
        return numElems;
    }

    void print()
    {
        for (size_t i = 0; i < size(); ++i)
            cout << getElem() << endl;
    }
    void printReverse()
    {
        for (size_t i = 0; i < size(); ++i)
            cout << getElemReverse() << endl;
    }

private:
    std::array<T, SIZE> arr;
    size_t numElems{0};
    int currentIndex{-1};
};
