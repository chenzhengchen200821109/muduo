# Any类  
类Any允许对任意类型进行类型安全的存储和取回。不象无类类型，Any保存了类型信息，  
并且不会让你在不知道正确类型的情况下获得存入的值。当然，有办法可以让你询问关  
于类型的信息，也有测试保存的值的方法，但最终，调用者必须知道在Any对象中的值的  
真实类型，否则不能访问Any。可以把Any看作为上锁的安全性。没有正确的钥匙，你不  
能进入其中。***any对它所保存的类型有以下要求：***  
1. CopyConstructible它必须可以复制这个类型  
2. Non-throwing destructor就象所有析构函数应该的那样
3. Assignable为了保证强异常安全(不符合可赋值要求的类型也可以用于Any, 但没有强异常安全的保证)  

# Any成员函数  
**1.any()**  
缺省构造函数创建一个空的Any实例，即一个不含有值的Any对象。  
当然，你无法从一个空的Any对象中取回值，因为没有值存在。  
**2.any(const any& other)**  
创建一个已有Any对象的独立拷贝。other中含有的值被复制并存入this  
**3.template<typename ValueType> any(const ValueType&)**  
这个模板构造函数存入一个传入的ValueType类型参数的拷贝。参数是一个  
const引用，因此传入一个临时对象来存入any是合法的。注意，该构造函数  
不是explicit的，如果是的话，Any会难以使用，而且也不会增加安全性。  
**4.~any()**  
析构函数销毁含有的值，但注意，由于对一个裸指针的析构不会调用operator delete   
或 operator delete[] ，所以在Any中使用指针时，你应该把裸指针包装成一个象shared_ptr  
那样的智能指针。  
**5.any& swap(any& other)**  
交换存在两个 any 对象中的值。  
**6.any& operator=(const any& other)**  
如果any实例非空，则丢弃所存放的值，并存入other值的拷贝  
**7.template<typename ValueType>  any& operator=(const ValueType& value)**  
如果any实例非空，则丢弃所存放的值，并存入 value 的一份拷贝，value可以是任意符合any  
要求的类型。  
**8.bool empty() const**  
给出any实例当前是否有值，不管是什么值。因而，当any持有一个指针时，即使该指针值为空，  
则empty()也返回 false。????  
**9.const std::type_info& type() const**  
给出所存值的类型。如果 any 为空，则类型为 void。   
# Any的普通函数
**1.template<typename ValueType>  ValueType any_cast(const any& operand)**   
any_cast让你访问Any对象中存放的值。参数为需要取回值的Any对象。如果类型ValueType与  
所存值不符，Any抛出一个异常。
**2.template<typename ValueType>  const ValueType* any_cast(const any* operand)**  
any_cast的一个重载，接受一个指向Any对象的指针，并返回一个指向所存值的指针。如果Any对象  
中的类型不是 ValueType, 则返回一个空指针。
**3.template<typename ValueType>  ValueType* any_cast(any* operand)**
any_cast的另一个重载，与前一个版本相似，但前一个版本使用const指针的参数并返回 const 指针，  
这个版本则不是。



