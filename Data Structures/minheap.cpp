#include <iostream>

class MinHeap
{
private:
    int *arr;
    int capacity;
    int size;

public:
    MinHeap(int cap)
    {
        capacity = cap;
        size = 0;
        arr = new int[cap];
    }

    // Function to get the index of the parent of a node
    int parent(int i)
    {
        return (i - 1) / 2;
    }

    // Function to insert a new element into the heap
    void insert(int value)
    {
        if (size == capacity)
        {
            std::cout << "Heap is full. Cannot insert." << std::endl;
            return;
        }

        // Insert the new element at the end
        int i = size;
        arr[i] = value;
        size++;

        // Maintain the min-heap property by bubbling up the element
        while (i > 0 && arr[i] < arr[parent(i)])
        {
            // Swap the element with its parent
            std::swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }

    // Function to extract the minimum element from the heap
    int extractMin()
    {
        if (size <= 0)
        {
            std::cout << "Heap is empty. Cannot extract minimum." << std::endl;
            return -1; // Assuming -1 represents an error or an empty heap
        }

        if (size == 1)
        {
            size--;
            return arr[0];
        }

        // Save the root element, and replace it with the last element
        int root = arr[0];
        arr[0] = arr[size - 1];
        size--;

        // Heapify the root element to maintain the min-heap property
        heapify(0);

        return root;
    }

    // Function to heapify a subtree with the root at a given index
    void heapify(int i)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < size && arr[left] < arr[i])
            smallest = left;
        if (right < size && arr[right] < arr[smallest])
            smallest = right;

        if (smallest != i)
        {
            // Swap the smallest element with the current element
            std::swap(arr[i], arr[smallest]);
            // Recursively heapify the affected subtree
            heapify(smallest);
        }
    }

    // Function to print the heap
    void printHeap()
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main()
{
    MinHeap minHeap(10);

    minHeap.insert(4);
    minHeap.insert(2);
    minHeap.insert(8);
    minHeap.insert(1);

    std::cout << "Min Heap: ";
    minHeap.printHeap();

    std::cout << "Extracted Min: " << minHeap.extractMin() << std::endl;

    std::cout << "Min Heap after extraction: ";
    minHeap.printHeap();

    return 0;
}
