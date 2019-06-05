#ifndef MUDUO_BASE_ANY_H
#define MUDUO_BASE_ANY_H

//reference:http://www.two-sdg.demon.co.uk/curbralan/papers/ValuedConversions.pdf 
#include <algorithm>
#include <typeinfo>
#include <exception>

namespace muduo
{
    class Any
    {
        public:
            Any() : content(0)
            {
            }
            Any(const Any& other)
                : content(other.content ? other.content->clone() : 0)    
            {
            }
            ~Any()
            {
                delete content;
            }
            const std::type_info& type_info() const
            {
                return content ? content->type() : typeid(void);
            }
            Any& swap(Any& rhs)
            {
                 std::swap(content, rhs.content);
                 return *this;
            }
            Any& operator=(const Any& rhs)
            {
                Any temp(rhs);
                return swap(temp);
            }
            operator const void *() const
            {
                return content;
            }
        public:
	        template<typename ValueType>
            Any(const ValueType& value) : content(new holder<ValueType>(value))
            {
            }
            template<typename ValueType>
            Any& operator=(const ValueType& rhs)
            {
                Any(rhs).swap(*this);
                return *this;
            }
            // what for?
            template<typename ValueType>
            bool copy_to(ValueType& value) const
            {
                const ValueType* copyable = to_ptr<ValueType>();
                if (copyable)
                    value = *copyable();
                return copyable;
            }
            template<typename ValueType>
            const ValueType* to_const_ptr() const
            {
                return type_info() == typeid(ValueType) ? &static_cast<holder<ValueType> *>(content)->held : 0;
            }
            template<typename ValueType>
            ValueType* to_ptr() const
            {
                return type_info() == typeid(ValueType) ? &(static_cast<holder<ValueType> *>(content))->held : 0;
            }
        private:
            class placeholder
            {
                public:
                    virtual ~placeholder() {}
                public:
                    virtual const std::type_info& type() const = 0;
                    virtual placeholder* clone() const = 0;
            };
            //holder contains the actual value we care about.
            template<typename ValueType>
            class holder : public placeholder
            {
                public:
                    holder(const ValueType& value) : held(value)
                    {
                    }
                public:
                    virtual const std::type_info& type() const
                    {
                        return typeid(ValueType);
                    }
                    virtual placeholder* clone() const
                    {
                        return new holder(held);
                    }
                public:
                    ValueType held;
            };
            placeholder* content;
    };

    template<typename ValueType>
    ValueType any_cast(const Any& operand)
    {
        ValueType *result = operand.to_ptr<ValueType>();
        return result ? *result : throw std::bad_cast();
    }

    template<typename ValueType>
    const ValueType* any_cast(const Any* operand)
    {
        const ValueType* result = operand->to_const_ptr<ValueType>();
        return result ? result : throw std::bad_cast();
    }

    template<typename ValueType>
    ValueType* any_cast(Any* operand)
    {
        ValueType* result = operand->to_ptr<ValueType>();
        return result ? result : throw std::bad_cast();
    }

} //namespace muduo 


#endif 
