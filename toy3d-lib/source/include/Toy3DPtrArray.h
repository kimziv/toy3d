
#ifndef _TOY3D_PTR_ARRAY_H
#define _TOY3D_PTR_ARRAY_H

#include "Toy3DCommon.h"


TOY3D_BEGIN_NAMESPACE

    typedef void* TPointer;

    class TPtrArray
    {
    protected: 
        TPointer *mPtr;  /* the pointer array data */
        Uint mLength;    /* the actual number of elements in the array */
        Uint mAllocLen;  /* the capacity, that is the number of elements, of the array */

    public:
        TPtrArray();
        ~TPtrArray();

        Bool create(); 
        Bool create(Uint size); 

        Bool remove(TPointer ptr);

        /*
         * Remove the element at the index from pointer array,
         * and the length of pointer array will be substracted 1, after calling.
         */
        const TPointer removeByIndex(Uint index); /* index begin with 0 */

        /*
         * Clear all the pointers in the array, and you should free their memory first.
         */
        void clearAll();

        void destroy(); 
        
        //process 
        Bool insert(TPointer ptr, Uint index);    /* index begin with 0 */
        Bool append(TPointer ptr);

        /*
         * Warning:
         *   If the element, at the index of the ptr array, is not null,
         *   you should free the memory related before calling this function.
         */
        void setElement(TPointer ptr, Uint index);

        /*
         * Warning:
         *   When you reduce the length of the array by this function,
         *   and if the memory, which the reduced section pointed to, contains any pointer,
         *   you should free the memory, which these inner pointers pointed to, if any. 
         */
        Bool setSize(Uint length);

        /*
         * name :     getElement
         * function : get elelment at the customed index,
         *   and you will get NULL pointer when the index is out of bound.
         */
        TPointer getElement(Uint index); 
        //TPointer* getAllElements(Uint *count);
        const Uint getLength(); 
        const Uint getAllocLength(); 
        
        //override operator[], and operator= 
        TPointer operator[](Uint index);
        const TPointer operator[](Uint index) const;

        /*
         * warning: if there is any vlaue in the left object of '=', you should free it first.
         */
        TPtrArray& operator=(const TPtrArray & ptrArray);

    private: 
        inline Uint nearestPowOf2 (Uint num);
        inline Bool expand(Uint length);

        /*
         * function: move backward(one step or more), for all the elements after the index(including),
         *     in order to get mPtr[index].
         */
        inline Bool moveBackward(Uint index);

        /*
         * function:
         *   move forward one step, for all the elements after the index(including),
         *   and get the TPointer, which is removed.
         */
        inline const TPointer moveForward(Uint index);
    };

TOY3D_END_NAMESPACE

#endif
