template <typename Object_type> struct ArrayList
{
private:
	Object_type* elements;
	int count;
	int capacity;

public:
	ArrayList();
	ArrayList(int initial_length);
	Object_type operator [](unsigned int index);
	void add(Object_type element);
	void remove(unsigned int index);
	Object_type get(unsigned int index);
	int indexOf(Object_type element);
	void destroy();
	bool contains(Object_type element);
	int count();
	void clear();
};

template<typename Object_type>
ArrayList<Object_type>::ArrayList()
{
	elements = new Object_type[5];
	capacity = 5;
	count = 0;
}

template<typename Object_type>
ArrayList<Object_type>::ArrayList(int initial_length)
{
	elements = new Object_type[initial_length];
	capacity = initial_length;
	count = 0;
}

template<typename Object_type>
Object_type ArrayList<Object_type>::operator[](unsigned int index)
{
	return get(index);
}

template<typename Object_type> void
ArrayList<Object_type>::add(Object_type element)
{
	if (capacity > count)
	{
		elements[count] = element;
		count++;
	}
	else
	{
		Object_type* new_elements = new Object_type[count + 1];
		for (int i = 0; i < count; i++)
		{
			new_elements[i] = elements[i];
		}
		new_elements[count] = element;
		elements = new_elements;
		count++;
		capacity++;
	}
}

template<typename Object_type> void
ArrayList<Object_type>::remove(unsigned int index)
{
	if (index < count)
	{
		count--;
		Object_type* remaining = new Object_type[count];
		for (int i = 0; i < count; i++)
		{
			if (i < index)
			{
				remaining[i] = elements[i];
			}
			else
			{
				remaining[i] = elements[i + 1];
			}
		}
		elements = remaining;
		capacity = count;
	}
}

template<typename Object_type> Object_type
ArrayList<Object_type>::get(unsigned int index)
{
	if (index < count)
	{
		return elements[index];
	}
	else return NULL;
}

template<typename Object_type> int
ArrayList<Object_type>::indexOf(Object_type element)
{
	for (int i = 0; i < count; i++)
	{
		if (elements[i] == element) return i;
	}
	return -1;
}

template<typename Object_type>
void ArrayList<Object_type>::destroy()
{
	count = 0;
	capacity = 0;
}

template<typename Object_type>
bool ArrayList<Object_type>::contains(Object_type element)
{
	int i = 0;
	while (i < count)
	{
		elements[i] == element ? return true : i++;
	}
	return false;
}

template<typename Object_type>
int ArrayList<Object_type>::count()
{
	return count;
}

template<typename Object_type>
void ArrayList<Object_type>::clear()
{
	count = 0;
	capacity = 1;
	delete[] elements;
	elements = new Object_type[1];
}
