#include <iostream>

template <typename T>
class DynamicArray
{
    private:
        T* arr;
        size_t size;
        size_t capacity;
    public:
        DynamicArray() : arr(nullptr), size(0), capacity(0) {}
        ~DynamicArray()
        {
            delete[] arr; 
        }
        size_t getSize() const
        {
            return size;
        }
        size_t getCapacity() const
        {
            return capacity;
        }

        bool empty() const
        {
            return size == 0;
        }


        void setCapacity(size_t newCapacity)
        {
            if(newCapacity < size)
            {
                throw std::out_of_range("New capacity is less than the current size.");                
            }
            T* newArr = new T[newCapacity];
            for(size_t i = 0; i < size; ++i)
            {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
            capacity = newCapacity;
        }



        // Push back an element
        void push_back(const T& value) 
        {
            if (size >= capacity) 
            {
                size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
                setCapacity(newCapacity);
            }
            arr[size++] = value;
        }

        // Insert an element at a given position
        void insert(size_t position, const T& value) 
        {
            if (position > size) 
            {
                throw std::out_of_range("Invalid position.");
            }

            if (size >= capacity) 
            {
                size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
                setCapacity(newCapacity);
            }

            for (size_t i = size; i > position; --i) 
            {
                arr[i] = arr[i - 1];
            }

            arr[position] = value;
            ++size;
        }

        // Insert 'count' copies of 'value' starting from a given position
        void insert(size_t position, const T& value, size_t count) 
        {
            for (size_t i = 0; i < count; ++i) 
            {
                insert(position, value);
            }
        }

        // Insert elements from an array starting from a given position
        void insert(size_t position, const T* values, size_t count) 
        {
            for (size_t i = 0; i < count; ++i) 
            {
                insert(position + i, values[i]);
            }
        }

        // Insert elements from another DynamicArray starting from a given position
        void insert(size_t position, const DynamicArray& other) 
        {
            insert(position, other.arr, other.size);
        }

        // Pop back an element
        void pop_back() 
        {
            if (size == 0) 
            {
                throw std::underflow_error("Array is empty.");
            }

            --size;
        }

        // Remove an element at a given position
        void remove(size_t position) 
        {
            if (position >= size) 
            {
                throw std::out_of_range("Invalid position.");
            }

            for (size_t i = position; i < size - 1; ++i) 
            {
                arr[i] = arr[i + 1];
            }

            --size;
        }

        // Remove 'count' elements starting from a given position
        void remove(size_t position, size_t count) 
        {
            for (size_t i = 0; i < count; ++i) 
            {
                remove(position);
            }
        }

        // Shrink the capacity to match the size
        void shrink_to_fit() 
        {
            setCapacity(size);
        }

        // Clear the array
        void clear() 
        {
            delete[] arr;
            arr = nullptr;
            size = 0;
            capacity = 0;
        }

        // Resize the array to a given size, filling with 'value' if necessary
        void resize(size_t newSize, const T& value = T()) 
        {
            if (newSize < size) 
            {
                size = newSize;
            } 
            else if (newSize > size) 
            {
                if (newSize > capacity) 
                {
                    setCapacity(newSize);
                }
                for (size_t i = size; i < newSize; ++i) 
                {
                    arr[i] = value;
                }
                size = newSize;
            }
        }

        // Iterator support
        T& operator[](size_t index) 
        {
            if (index >= size) 
            {
                throw std::out_of_range("Index out of bounds.");
            }
            return arr[index];
        }

        const T& operator[](size_t index) const 
        {
            if (index >= size) 
            {
                throw std::out_of_range("Index out of bounds.");
            }
            return arr[index];
        }
};



int main() 
{
    DynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    std::cout << "Size: " << arr.getSize() << ", Capacity: " << arr.getCapacity() << std::endl;

    arr.insert(1, 4);
    arr.pop_back();

    for (size_t i = 0; i < arr.getSize(); ++i) 
    {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}
