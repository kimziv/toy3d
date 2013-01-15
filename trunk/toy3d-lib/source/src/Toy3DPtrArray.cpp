
#include "Toy3DPtrArray.h"


TOY3D_BEGIN_NAMESPACE

    TPtrArray::TPtrArray()
    {
        mPtr = NULL;
        mLength = 0;
        mAllocLen = 0;
    }

    TPtrArray::~TPtrArray()
    {
    }

    Bool TPtrArray::create()
    {
        mLength = 0;
        mAllocLen = DEFAULT_PTR_ARRAY_SIZE;
        mPtr = (TPointer *)malloc(sizeof(TPointer) * DEFAULT_PTR_ARRAY_SIZE);
        if(mPtr)
            return TRUE;

        return FALSE;
    }

    Bool TPtrArray::create(Uint size)
    {
        mLength = 0;
        mAllocLen = size;
        mPtr = (TPointer *)malloc(sizeof(TPointer) * size);
        if(mPtr)
            return TRUE;

        return FALSE;
    }

    Bool TPtrArray::remove(TPointer ptr)
    {
        Uint i;
        Uint length = mLength-1;
        for(i=0; i<length; i++)
        {
            if(mPtr[i]==ptr)
            {
                moveForward(i);
                return TRUE;
            }
        }

        //TOY3D_TIPS("Error: the pointer doesn't exist in the pointer array.\n");
        return FALSE;
    }

    const TPointer TPtrArray::removeByIndex(Uint index)
    {
        return moveForward(index);
    }

    void TPtrArray::clearAll()
    {
        Uint i;
        for(i=0; i<mLength; i++)
        {
            mPtr[i] = 0;
        }

        mLength = 0;

        return;
    }

    void TPtrArray::destroy()
    {
        FREEANDNULL(mPtr);
        mLength = 0;
        mAllocLen = 0;

        return;
    }

    Bool TPtrArray::insert(TPointer ptr, Uint index)
    {
        Bool rv;
        rv = moveBackward(index);
        if(FALSE==rv)
            return FALSE;

        mPtr[index] = ptr;
        return TRUE;
    }

    Bool TPtrArray::append(TPointer ptr)
    {
        Bool rv;
        rv = expand(1);
        if(FALSE==rv)
            return FALSE;

        mPtr[mLength] = ptr;
        mLength++;

        return TRUE;
    }

    void TPtrArray::setElement(TPointer ptr, Uint index)
    {
        if(index>=mLength)
        {
            Uint length, i;
            length = index-mLength+1;
            expand(length);
            for(i=0;i<length;i++)
            {
                mPtr[mLength+i] = 0;
            }
            mLength = index+1;
        }

        mPtr[index] = ptr;
        
        return;
    }

    Bool TPtrArray::setSize(Uint length)
    {
        Bool rv;
        if(mLength<length)
        {
            rv = expand(length-mLength);
            if(FALSE==rv)
                return FALSE;

            mLength = length;
        }

        return TRUE;
    }

    TPointer TPtrArray::getElement(Uint index)
    {
        if(index>=mLength)
            return NULL;

        return mPtr[index];
    }

    const Uint TPtrArray::getLength()
    {
        return (const Uint)mLength;
    }

    const Uint TPtrArray::getAllocLength()
    {
        return (const Uint)mAllocLen;
    }

    TPointer TPtrArray::operator[](Uint index)
    {
        if(index>=mLength)
        {
            return (TPointer)NULL;
        }
        
        return mPtr[index];
    }

    const TPointer TPtrArray::operator[](Uint index) const
    {
        if(index>=mLength)
        {
            return NULL;
        }

        return mPtr[index];
    }

    TPtrArray& TPtrArray::operator=(const TPtrArray & ptrArray)
    {
        destroy();
        create(ptrArray.mAllocLen);
        mLength = ptrArray.mLength;

        memcpy( mPtr, ptrArray.mPtr, mAllocLen*sizeof(TPointer *) );

        return *this;
    }


//////////////////////////////////////////////////////////////////////////
//private function
    inline Uint TPtrArray::nearestPowOf2 (Uint num)
    {
        Uint n = 1;
        while (n < num)
            n <<= 1;

        return n;
    }

    inline Bool TPtrArray::expand(Uint length)
    {
        Uint want_alloc = mLength+length;

        if(want_alloc>mAllocLen)
        {
            Uint old_alloc = mAllocLen;
            mAllocLen = nearestPowOf2(want_alloc);
            mPtr = (TPointer *)realloc(mPtr, mAllocLen*sizeof(TPointer));
            if( !mPtr )
            {
                TOY3D_TIPS("Failed to realloc memory for TPtrArray.\n");
                return FALSE;
            }

            memset(mPtr+old_alloc, 0, mAllocLen-old_alloc);
        }

        return TRUE;
    }

    inline Bool TPtrArray::moveBackward(Uint index)
    {
        Uint i, length;
        Bool rv;

        /* if the index is greater than the actual number of elements */
        if(index>=mLength)
        {
            length = index - mLength + 1;
            rv = expand(length);
            if(FALSE==rv)
                return FALSE;

            for(i=0; i<length; i++)
            {
                mPtr[mLength+i] = 0;
            }

            mLength += length;
            return TRUE;
        }

        //else
        rv = expand(1);
        if(FALSE==rv)
            return FALSE;

        for( i=mLength; i>index; i--)
            mPtr[i] = mPtr[i-1];

        mPtr[index] = 0;
        mLength++;

        return TRUE;
    }

    inline const TPointer TPtrArray::moveForward(Uint index)
    {
        Uint i, length;
        TPointer temp;

        if(index>=mLength)
            return NULL;

        temp = mPtr[0];
        length = mLength - 1;

        for( i=index; i<length; i++)
            mPtr[i] = mPtr[i+1];

        mPtr[length] = 0;
        mLength--;

        return (const TPointer)temp;
    }



TOY3D_END_NAMESPACE
