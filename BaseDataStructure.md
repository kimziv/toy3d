# 指针数组 #



## 基本原则 ##
  * 数组元素是指针
  * 数组长度可动态增加
  * 支持各种数据类型，类似C++模板。


## 动态变化策略 ##
数组增长：
当已分配长度不够时，重新分配内存，按照如下原则(假设需求长度为n，实际分配长度为x)：
x=2^m >= n，其中m取可取的最小整数。


## 几个需要考虑的问题 ##

  * 插入元素时，索引越界的情况怎样处理？

此处的越界是指定的索引值超出实际最大索引至少2。即如下情况：
```
    Mesh *temp = new Mesh();
    mPtrArray[0] = temp;//此时 length = 1;
    //接下来执行如下操作，都将发生越界;
    mPtrArray[3] = temp;
    insert((TPointer)temp, 3);
```
放弃的解决方案：中间的值设置为空值NULL。（就上述例子来说，执行完第三句，将出现如下结果：）
```
    mPtrArray[1] 值为 NULL;
    mPtrArray[2] 值为 NULL;
    mPtrArray[3] 值为 temp;
    mPtrArray.length 值为 4.
```
最终方案：只允许append和insert函数在需要的时候扩展数组长度，并且每次操作完成后数组元素个数只允许增加1（在insert时，如果指定的索引超出数组最大索引2或以上，则返回错误）；而数组下标，类似setElement函数，只能处理已经存在的元素。例如
```
    Mesh *temp1, *temp2, *temp3, *temp4;
    temp1 = new Mesh();
    mPtrArray[0] = temp;      //此时 mPtrArray[0]值为NULL，此语句编译不过
    temp2 = new Mesh();
    insert((TPointer)temp, 2);//failed

    temp3 = new Mesh();
    insert((TPointer)temp, 0);//ok
    temp4 = new Mesh();
    mPtrArray.append(temp);   //ok

    delete temp1;
    delete temp2;
    delete temp3;
    delete temp4;
```

  * 删除时如何释放指针里的数据？glib 里要自己设置 set\_clear\_fun 函数。
> > 即：任何类型都是当作“void指针”来存储的，如果该指针已经动态分配了数据，对应的内存怎样释放？


> 解决：按照目前的设计方案，处理资源分配释放的是资源对应的Manager类，这些类里都提供了destroy函数，可以在该函数中完成资源占用的内存的释放，再调用mPtrArray.destroy()即可。详见“用户使用”部分。

> 与此类似的一种情况，当用户调用setSize或者使用下标来给数组元素赋值时，如果发生缩减数组的情况，数组元素对应的内存里的指针，由用户自己释放。说明如下：
```
    //假设当前length=8，以Mesh类型为例。
    Uint length = mPtrArray.getLength();
    Mesh *mesh;
    for(Uint i=0;i<length;i++)
    {
        mesh = (Mesh *)mPtrArray.getElement(i);
        delete mesh;
    }
    setSize(0);

    //使用下标时
    Mesh *mesh;
     if(mPtrArray[0])
    {
        mesh = (Mesh *)mPtrArray[0];
        delete mesh;
    }
    mesh = new Mesh();
    mPtrArray[0] = (TPointer)mesh;
```

  * 操作符[.md](.md)重载存在问题。

## 类 ##

```
typedef void* TPointer;

class TPtrArray {
    protected: 
        TPointer *mPtr;  /* the pointer array data */
        Uint mLength;    /* the actual number of elements in the array */
        Uint mAllocLen;  /* the capacity, that is the number of elements, of the array */

    public:
        TPtrArray();
        ~TPtrArray();

        //create 
        void create(); 
        void create(Uint size); 
        
        //delete 
        Bool remove(TPointer ptr); 
        TPointer* removeByIndex(Uint index); /* index begin with 0 */
        void destroy(); 
   
        //process 
        Bool insert(TPointer ptr, Uint index); /* index begin with 0 */
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
        void setSize(Uint length); 
        
        TPointer getElement(Uint index); 
        Uint getLength(); 
        Uint getAllocLength(); 
        
        //override operator[], and operator= 
        TPointer operator[](Uint index);
        const TPointer operator[](Uint index) const;

        /* Function : override operator= 
         * warning: if there is any vlaue in the left object of '=', you should free it first.
         */
        const TPtrArray& operator=(const TPtrArray & ptrArray);

    private:
        inline Uint nearestPowOf2(Uint num);
        inline Bool expand(Uint length);

        /*
         * function: move backward(one step or more), for all the elements after the index(including),
         *     in order to get mPtr[index].
         */
        inline Bool moveBackward(Uint index);

        /*
         * function:
         *   move forward one step, for all the elements after the index(including)
         *   and get the TPointer, which is removed.
         */
        inline const TPointer moveForward(Uint index);
};

```


## 用户使用 ##

```

    //Sample code for Toy3DPtrArray
    //You can also take MeshManager as example.

    TPtrArray *pPtrArray;
    Mesh *pMesh, *pTemp;

    mPtrArray = new TPtrArray();
    mPtrArray.create();
    pMesh = new Mesh();
    if( !pMesh )
    {
        printf("ceate mesh failed.\n");
        return;
    }

    //There are 4 ways to add elemet to mPtrArray.
    //1st
    mPtrArray[0] = pMesh;

    //2st
    mPtrArray.append((TPointer)pMesh );

    //3rd
    mPtrArray.insert((TPointer)pMesh, mPtrArray.getLength());

    //4th
    mPtrArray.setElement((TPointer)pMesh, mPtrArray.getLength());

    //If you want to modify an existing element. You can...
    pTemp = (Mesh *)mPtrArray.getElement(0);
    if(pTemp )
    {
        delete pTemp;
        mPtrArray.setElement((TPointer)pMesh, 0);
    }

    //If you want to remove an element from pointer array. You can...
    pTemp = mPtrArray.removeByIndex(0);
    if(pTemp)
    {
        delete pTemp;
    }

    //free memory and delete pointer array
    Uint length = mPtrArray->getLength();
    while(length--)
    {
        pTemp = (Mesh *)mPtrArray->getElement(length);
        delete pTemp;
    }
    mPtrArray->destroy();
    delete mPtrArray;

```

# Reference #

  * [glib Manual](http://developer.gnome.org/glib/2.34/)