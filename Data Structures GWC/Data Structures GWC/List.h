#ifndef LIST_H // // multiple inclusion guard
#define LIST_H

template <typename Object>
class List
{
private:
	struct Node // private member structure (could be class instead)
	{
		Object data;
		Node* prev;
		Node* next;
		Node(const Object& d = Object(), Node* p = NULL, Node* n = NULL) // constructor
			: data(d), prev(p), next(n) {}
		Node(Object&& d, Node* p = NULL, Node* n = NULL) // move constructor (C++11)
			: data(move(d)), prev(p), next(n) {}
	};

public:
	class const_iterator // **********************************************
	{
	public:
		const_iterator() : current(NULL) {} // default constructor
		const Object& operator*() const // const de-referencing
		{
			return retrieve();
		}

		const_iterator& operator++() // pre-increment
		{
			current = current->next;
			return *this;
		}
		const_iterator operator++(int) // post-increment
		{
			const_iterator old = *this;
			++(*this);
			return old;
		}

		const_iterator& operator--() // pre-decrement
		{
			current = current->prev;
			return *this;
		}

		const_iterator operator--(int) // post-decrement
		{
			const_iterator old = *this;
			--(*this);
			return old;
		}
		
		bool operator== (const const_iterator& rhs) const
		{
			return current == rhs.current;
		}

		bool operator != (const const_iterator& rhs) const
		{
			return !(*this == rhs);
		}

	protected:
		Node* current;
		Object& retrieve() const
		{
			return current->data;
		}
		const_iterator(Node* p) : current(p) {} // constructor
		friend class List<Object>;
	}; // end class const_iterator // **********************************************
	class iterator : public const_iterator // **************************************
	{
	public:
		iterator() : current(NULL) {} // default constructor
		Object& operator*() // de-referencing
		{
			return retrieve();
		}

		const Object& operator*() const // const de-referencing
		{
			return const_iterator::operator*();
		}

		iterator& operator++() // pre-increment
		{
			current = current->next;
			return *this;
		}

		iterator operator++(int) // post-increment
		{
			iterator old = *this;
			++(*this);
			return old;
		}

		iterator& operator--() // pre-decrement
		{
			current = current->prev;
			return *this;
		}
		iterator operator--(int) // post-decrement
		{
			iterator old = *this;
			--(*this);
			return old;
		}

	private: // we are not expecting to derive from iterator...
		iterator(Node* p) : const_iterator(p) {} // constructor
		friend class List<Object>;
	};// end class iterator // **********************************************
	// back to class List:

public:
	// constructors
	List() // default
	{
		init();
	}

	List(const List& rhs) // copy constructor
	{
		init();
		for (const Object& x : rhs) // range-based for loop (C++11)
			push_back(x);
	}

	List(List&& rhs) // move constructor (C++11)
		: theSize(rhs.theSize), head(rhs.head), tail(rhs.tail)
	{
		rhs.theSize = 0;
		rhs.head = NULL;
		rhs.tail = NULL;
	}

	// destructor
	~List()
	{
		clear();
		delete head;
		head = NULL;
		delete tail;
		tail = NULL;
	}

	// public assignment operator
	List& operator=(const List& rhs)
	{
		if (this != &rhs) // prevent assignment to itself
		{
			this->clear();
			for (const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr)
				this->push_back(*itr);
		}
		return *this;
	}

	iterator begin()
	{
		return iterator(head->next);
	}

	const_iterator begin() const
	{
		return const_iterator(head->next);
	}

	iterator end()
	{
		return iterator(tail);
	}

	const_iterator end() const
	{
		return const_iterator(tail);
	}

	size_t size() const
	{
		return theSize;
	}

	bool empty() const
	{
		return size() == 0;
	}

	void clear()
	{
		while (!empty())
			pop_front();
	}

	Object& front()
	{
		return *begin();
	}

	const Object& front() const
	{
		return *begin();
	}

	Object& back()
	{
		return *--end();
	}

	const Object& back() const
	{
		return *--end();
	}

	void push_front(const Object& x)
	{
		insert(begin(), x);
	}

	void push_back(const Object& x)
	{
		insert(end(), x);
	}

	void pop_front()
	{
		erase(begin());
	}

	void pop_back()
	{
		erase(--end());
	}

	// Insert copy of x on the free store before itr:
	iterator insert(iterator itr, const Object& x)
	{
		Node* p = itr.current;
		theSize++;
		try
		{
			// new Node allocated on the freestore
			p->prev = p->prev->next = new Node(x, p->prev, p);
		}
		// if memory allocation failed:
		catch (...) // executes in case of exception (error)
		{
			cout << "Error encountered... quitting, sorry!n";
			system("pause");
			exit(EXIT_FAILURE); // quit
		}
		return iterator(p->prev);
	}
	// Erase item at itr:
	iterator erase(iterator itr)
	{
		if (!empty())
		{
			Node* p = itr.current;
			iterator retVal(p->next);
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delete p;
			p = NULL;
			theSize--;
			return retVal;
		}
		else
		{
			cout << "List empty!n";
			return NULL;
		}
	}
	// Erase items from start to end:
	iterator erase(iterator start, iterator end)
	{
		for (iterator itr = start; itr != end;)
			itr = erase(itr);
		return end;
	}
private:
	size_t theSize;
	Node* head;
	Node* tail;
	void init()
	{
		theSize = 0;
		try
		{
			head = new Node; // on the free store
			tail = new Node; // on the free store
		}
		// if memory allocation failed:
		catch (...) // executes in case of exception (error)
		{
			cout << "Error encountered... quitting, sorry!n";
			system("pause");
			exit(EXIT_FAILURE); // quit
		}
		head->next = tail;
		tail->prev = head;
	}
};// end class File
#endif
