// Provided by: Daniel Nichols
// Course number: CIS-221
// Assignment 2
// I did not copy code from other sources or people, and I did not share 
// my code with anyone else.
// FILE: sequence.cpp
// CLASS PROVIDED: sequence (part of the namespace main_savitch_4)

// INVARIANT for the sequence:
//
//   1. The number of value_types in the sequence is in the member variable used
//   2. For a non-empty sequence, the value_types in the sequence are
//      stored in order in data[0] through data[used-1].
//   3. current_index keeps track of the current location in data; whenever current_index
//      is greater than or equal to used, there is no current value_type.
//   4. capacity keeps track of the current capacity of the array pointed
//      to by data.  Capacity starts out with the value initial_capacity
//      and is changed by resize as needed (whenever used is greater than
//      or equal to capacity).



#include <cassert>   // Provides assert
#include <algorithm> // Provides copy()
#include "sequence.h"
using namespace std;

namespace main_savitch_4
{
    sequence::sequence(size_type initial_capacity)      // the main constructor
    // Library facilities used: cstdlib (included in the file sequence.h)
    {
        data=new double[initial_capacity];
        used=0;
        capacity=initial_capacity;
        current_index=0;
    }

    sequence::sequence(const sequence& source)          //  the copy constructor
    // Library facilities used: cstdlib
    {
        value_type *new_data;
        // Check if it is trying to copy itself.
        if(this != &source)
        {
            // If needed allocate an array with a different size.
            if(capacity!=source.capacity)
            {
                new_data= new value_type[source.capacity];
                data= new_data;
                capacity=source.capacity;
            }
        // Copy the data from the source array.
        used= source.used;
        std::copy(source.data, source.data + source.used, data);
        }
    }

    sequence::~sequence() // the destructor
    {
        delete [ ] data;
    }

    void sequence::start()
    {
        // Sets the current index to the beggining of the array if the array is not empty. 
        if(used != 0)
        {
            current_index=0;
        }
    }

    void sequence::advance()
    {
        // Make sure that their is a current index to advance.
        assert(is_item());
        current_index++;
    }

    void sequence::insert(const value_type& entry)
    {
        //Check to see if adding another value is within the current capacity.
        if(used+1>capacity)
        {
            // If not, increase the capacity.
            resize(capacity+3);
        }
        // If the array is empty then make the first index the entry and set it to the current index.
        if(used==0)
        {
            data[0]=entry;
            current_index=0;
        }
        // If the array is not empty and there is a current index. 
        else if(is_item())
        {
            // Starting at the end of the array shift each value over to the right until reaches the 
            // current index, then copy the value entered into the current index. 
            for(int index=used;index>current_index;index--)
            {
                data[index]=data[index-1];
            }   
            data[current_index]=entry;
        }
        // If the array is not empty, but doesn't have a valid current index, then shift all the data 
        // to the right one and put the entry in the very beggining of the array. 
        else
        {
            for(int index=used; index>0;index--)
            {
                data[index]=data[index-1];
            }
            data[0]=entry;
        }
        used++;
    }

    void sequence::attach(const value_type& entry)
    {
        //Check to see if adding another value is within the current capacity.
        if(used+1>capacity)
        {
            resize(capacity+3);
        }
        // If the array is empty then make the first index the entry and set it to the current index.
        if(used==0)
        {
            data[0]=entry;
            current_index=0;
        }
        // Starting at the end of the array shift each value over to the right until reaches the 
        // current index +1, then copy the value entered into the current index +1 and set the 
        // current index accordingly. 
        else if(is_item())
        {
            for(int index=used;index>current_index+1;index--)
            {
                data[index]=data[index-1];
            }   
            data[current_index+1]=entry;
            current_index=current_index+1;
        }
        // If the array is not empty, but doesn't have a valid current index, then shift all the data 
        // to the right one and put the entry in the very end of the array. 
        else
        {
            data[used]=entry;
        }
        used++;
    }

    void sequence::remove_current()
    {
        // Make sure that there is a current index to remove.
        assert(is_item());
        // Shift all the values after the current index to the left one thus 
        // replacing the value that was meant to be removed.
        for(int index=current_index;index<used-1;index++)
        {
            data[index]=data[index+1];
        }
        // Decrease the size of the array
        used--;
        // Make sure that if the array is empty that the current index is not 0.
        if(used==0)
        {
            current_index=1;
        }

    }

    void sequence::resize(size_type new_capacity)
    {
        value_type *larger_data; // Declare new pointer
        if(new_capacity == capacity)
        {
            return;
        }
        if(new_capacity < used)
        {
            // Can't resize less than what already being used
            new_capacity =used;
        }
        // Create a new array and copy the current data to a new array and delete the existing array.
        larger_data = new value_type[new_capacity];
        copy(data, data + used, larger_data);
        delete [ ] data;
        data= larger_data;
        capacity=new_capacity;
    }

    void sequence::operator =(const sequence& source)
    {
        value_type *new_data;
        // Check for self-assignment
        if( this == &source)
        {
            return;
        }
        // If needed resize space for a new array with a different size.
        if(capacity != source.capacity)
        {
            new_data = new value_type[source.capacity];
            delete [ ] data;
            data= new_data;
            capacity=source.capacity;
        }
        // Copy the data from the source array. 
        used= source.used;
        copy(source.data, source.data + used, data);
    }

    sequence::size_type sequence::size() const
    {
        return used;
    }

    bool sequence::is_item() const
    {
        if(current_index >= used || current_index < 0)
        {
            return false;
        }
        return true;
    }

    sequence::value_type sequence::current() const
    {
       assert(is_item()==true);
       return data[current_index];
    }

}
