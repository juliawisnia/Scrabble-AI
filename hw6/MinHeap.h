#include <iostream>
#include <vector>
#include <stdexcept>
#include <exception>

template <class T>
class MinHeap {
    public:
      /* Constructor that builds a d-ary Min Heap
      This should work for any d >= 2,
      but doesn't have to do anything for smaller d.*/
      MinHeap (int d) {
        ary = d;
      }

      ~MinHeap () {}

      /* adds the item to the heap, with the given priority. */
      void add (T item, int priority) {
        std::pair<T, int> add(item, priority);
        items.push_back(add);
        heapifyUp();
      }

      /* returns the element with smallest priority.  
      Break ties however you wish.  
      Throws an exception if the heap is empty. */
      const T & peek () const {
        if (isEmpty()) throw std::out_of_range;
        return items[0].first;
      }

      /* removes the element with smallest priority.
      Break ties however you wish.
      Throws an exception if the heap is empty. */
      void remove () {
        if (isEmpty()) throw std::out_of_range;
        items[0] = items[items.size() - 1];
        items.pop_back();
      }

      /* returns true iff there are no elements on the heap. */
      bool isEmpty () {
        if (items.empty()) return true;
        else return false;
      }

  private:
      std::vector<std::pair<T, int> > items;
      int ary;
      
      void swap(int indexOne, int indexTwo) {
        std::pair<T, int> temp = items[indexOne];
        items[indexOne] = items[indexTwo];
        items[indexTwo] = temp;
      }

      void heapifyDown() {
        int index = items[0];
        while (hasChild(index)) {
          if (items[index] < items[getSmallestChildIndex()]) break;
          else {
            swap(index, getSmallestChildIndex());
            index = getSmallestChildIndex();
          }
        }
      }

      void heapifyUp() {
        int index = items.size() - 1;
        while (hasParent(index) && getParentPriority(index) > items[index].second) {
          swap(getParentIndex(index), index);
          index = getParentIndex(index);
        }
      }

      bool hasParent(int index) {
        if ((index - index % ary)/ary >= 0) return true;
        else return false;
      }

      int getParentPriority(int index) {
        if (!hasParent(index)) return -1;
        return items[(index - index % ary)/ary].second;
      }

      int getParentIndex(int index) {
        if (!hasParent(index)) return -1;
        else return (index - index % ary)/ary;
      }

      bool hasChild(int index) {
        if (index*ary <= items.size()) return true;
        else return false;
      }

      int getSmallestChildIndex(int index) {
        if (!hasChild(index)) return -1;
        else {
          int childIndex = index*ary + 1;
          int smallestChild = -1;
          int smallestChildIndex;

          while (childIndex < items.size() && childIndex < index*ary + ary) {
            if (items[childIndex].second < smallestChild) {
              smallestChild = items[childIndex].second;
              smallestChildIndex = childIndex;
            }
            childIndex++;
          }
          return smallestChildIndex;
        }
      }
};