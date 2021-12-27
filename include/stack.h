// объявление и реализация шаблонного стека
// стек поддерживает операции:
// - вставка элемента,
// - извлечение элемента,
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту,
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

constexpr int memsize = 25;

template <typename T>
class Stack
{
private:
	T* pMem;
	int MemSize;
	int Hi;
	//virtual int GetNextIndex(int index);
public:
	Stack(int size = memsize)
	{
		if (size <= 0)
			throw std::exception("Size must be greater than null!");
		pMem = new T[size];
		MemSize = size;
		Hi = -1;
	}

	~Stack()
	{
		delete[] pMem;
	}

	void Put(const T& val)
	{
		if (Hi == (MemSize - 1))
		{
			T* tmp = new T[++MemSize];
			for (size_t i = 0; i < MemSize; i++)
				tmp[i] = pMem[i];
			delete[] pMem;
			pMem = tmp;
		}
		pMem[++Hi] = val;
	}

	T& Get()
	{
		if (IsEmpty())
			throw std::exception("Stack is empty!");
		return pMem[Hi--];
	}

	T View() const
	{
		if (IsEmpty())
			throw std::exception("Stack is empty!");
		return pMem[Hi];
	}

	int IsEmpty() const
	{
		return Hi == -1;
	}

	int GetDataCount() const
	{
		return Hi + 1;
	}

	void Clear()
	{
		Hi = -1;
	}
};