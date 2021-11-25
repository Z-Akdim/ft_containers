#ifndef VECTOR_HPP
#define VECTOR_HPP

// #include "ft_container.hpp"
#include "My_iterator.hpp"
namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
	{
        public:
                typedef T value_type;
                typedef Alloc allocator_type;
                typedef typename allocator_type::reference reference;
                typedef typename allocator_type::const_reference const_reference;
                typedef typename allocator_type::pointer pointer;
                typedef typename allocator_type::const_pointer const_pointer;
                typedef typename ft::MyIterator<value_type> iterator;
                typedef typename ft::MyIterator<const_pointer> const_iterator;
                typedef size_t  size_type;
        private:
                allocator_type _allocator;
                size_type _capacity;
                size_type _size;
                value_type *_arry;
        public:
        
                vector (const allocator_type& alloc = allocator_type()):
                        _allocator(alloc), _capacity(0), _size(0), _arry(NULL){};
                vector (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()): _allocator(alloc), _capacity(n), _size(n)
                {
                
                };

                template <class InputIterator>
                vector (InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type())
                {
                };

                vector (const vector& x);
                vector& operator= (const vector& x);
                ~vector();
        public:
                iterator begin(){return (iterator(_arry));}

                const_iterator begin() const{return (iterator(_arry));}

                iterator end(){return (iterator(_arry + _size));}

                const_iterator end() const{return (iterator(_arry + _size));}

                size_type size() const{return (_size);}

                size_type max_size() const
                {
                        return allocator_type().max_size(); 
                }
                
        void resize(size_type n, value_type val = value_type())
		{
			size_t i;
			if (n > _capacity)
			{
				_capacity = n;
				T *new_arr = _allocator.allocate(n);
				for (size_t i = 0; i < _size; i++)
					_allocator.construct(new_arr + i, _arry[i]);
				_arry = new_arr;
			}
			for (i = _size; i < n; i++)
				_allocator.construct(_arry + i, val);
			_size = n;
		}
                
        size_type capacity() const{return (_capacity);

        reference front(){return iterator(*_arry);

        const_reference front() const{return (*_arry);

        reference back(){return (*(_arry + _size - 1));

        const_reference back() const{return (*(_arry + _size - 1));

        reference at (size_type n){return (*(_arry + n));

        const_reference at (size_type n) const{return (*(_arry + n));

        bool empty() const
        {
                if (!_size)
                        return(true);
                return(false);
        }

		void reserve(size_type n)
		{
			if (_capacity >= n)
				return;
			T *new_arr = _allocator.allocate(n);
			for (size_t i = 0; i < _size; i++)
				_allocator.construct(new_arr + i, _arry[i]);
			for (size_t i = 0; i < _size; i++)
				_allocator.destroy(_arry + i);
			_allocator.deallocate(_arry, _capacity);
			_arry = new_arr;
			_capacity = n;
		}

        template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			for (size_t i = 0; i < _size; i++)
				_allocator.destroy(_arry + i);
			_size = 0;
			InputIterator tmp = first;
			while (tmp++ < last)
				_size++;
			if (_size > _capacity)
			{
				_allocator.deallocate(_arry, _capacity);
				_arry = _allocator.allocate(_size);
				_capacity = _size;
			}
			for (_size = 0; first < last; _size++)
			{
				_arry[_size] = *first;
				first++;
			}
		}
		
		void assign(size_t n, T val)
		{

			for (size_t i = 0; i < _size; i++)
				_allocator.destroy(_arry + i);
			if (n && n > _capacity)
			{
				_allocator.deallocate(_arry, _capacity);
				_arry = _allocator.allocate(n);
				_capacity = n;
			}
			for (size_t i = 0; i < n; i++)
				_allocator.construct(_arry + i, val);
			_size = n;
		}

		void push_back(const value_type &val)
		{
			if (_size >= _capacity)
			{
				if (_capacity)
				{
					T *new_arr = _allocator.allocate(_capacity * 2);
					for (size_t i = 0; i < _size; i++)
						_allocator.construct(new_arr + i, _arry[i]);
					for (size_t i = 0; i < _size; i++)
						_allocator.destroy(_arry + i);
					_allocator.deallocate(_arry, _capacity);
					_arry = new_arr;
					_capacity *= 2;
				}
				else
				{
					_capacity *= 2;
					_arry = _allocator.allocate(1);
					_capacity = 1;
				}
			}
			_allocator.construct( + _size, val);
			_size++;
		}

        void pop_back()
		{
			if (_size == 0)
				return;
			allocator_type().destroy( + --_size);
		}
		iterator erase(iterator position)
		{
			return vector::erase(position, position + 1);
		}

		iterator erase(iterator first, iterator last)
		{
			size_t count = 0;

			if (last < first)
				return first;
			if (last > vector::end())
				last = vector::end();
			for (; first + count != last; count++)
				;
			for (size_t i = 0; last + i < vector::end(); i++)
			{
				*(first + i) = *(last + i);
			}
			for (size_t i = 0; i < count; i++)
				_allocator.destroy(_arry + _size - 1 - i);
			_size -= count;
			return (first);
		}

		template <class data>
		void SwapData(data &x, data &y)
		{
			data tmp;
			tmp = x;
			x = y;
			y = tmp;
		}

		void swap(vector &x)
		{
			if (this == &x)
				return;
			else
			{
				this->SwapData(this->_arry, x._arry);
				this->SwapData(this->_size, x._size);
				this->SwapData(this->_capacity, x._capacity);
			}
		}

		template <class T, class Alloc>
		void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
		{
			x.swap(y);
		}

		void clear()
		{
			if (_size == 0)
				return ;
			for (size_t i = 0; i < _size; i++)
				_allocator.destroy(_arry + i);
			_size = 0;
		}
		allocator_type get_allocator() const { return _allocator; }
    };
};

#endif