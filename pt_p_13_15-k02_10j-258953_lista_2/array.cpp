#include "Array.h"
#include "PathEdge.h"

using namespace std;

template <typename T>
Array<T>::Array() : head(nullptr), size(0) 
{

}

template <typename T>
Array<T>::Array(const Array<T>& array)
{
	this->head = new T[array.size];
	for (size_t i = 0; i < array.size; i++)
	{
		this->head[i] = array.head[i];
	}
	this->size = array.size;
}

template <typename T>
Array<T>::~Array()
{
	if (this->head != nullptr)
	{
		delete[] this->head;
	}
}

template <typename T>
void Array<T>::addFront(const T& data)
{
	T* newHead = new T[this->size + 1];
	newHead[0] = data;

	//	Kopiowanie, jeœli dane istniej¹.
	if (this->head != nullptr)
	{
		for (size_t i = 0; i < this->size; i++)
		{
			newHead[i + 1] = this->head[i];
		}

		//	Usuniêcie starej tablicy.
		delete[] this->head;
	}

	this->size++;
	this->head = newHead;
}

template <typename T>
void Array<T>::addBack(const T& data)
{
	T* newHead = new T[this->size + 1];
	newHead[this->size] = data;

	//	Kopiowanie, jeœli dane istniej¹.
	if (this->head != nullptr)
	{
		for (size_t i = 0; i < this->size; i++)
		{
			newHead[i] = this->head[i];
		}

		//	Usuniêcie starej tablicy.
		delete[] this->head;
	}

	this->size++;
	this->head = newHead;
}

template <typename T>
bool Array<T>::addAt(const size_t& index, const T& data)
{
	//	Sprawdzenie czy indeks jest poprawny.
	if (index > this->size)
	{
		return false;
	}

	T* newHead = new T[this->size + 1];
	newHead[index] = data;

	//	Skopiowanie elementów znajduj¹cych siê przed konkretnym indeksem.
	for (size_t i = 0; i < index; i++)
	{
		newHead[i] = this->head[i];
	}

	//	Skopiowanie elementów znajduj¹cych siê po konkretnym indeksem.
	for (size_t i = index + 1; i <= size; i++)
	{
		newHead[i] = this->head[i - 1];
	}

	delete[] this->head;
	this->size++;
	this->head = newHead;
	return true;
}

template <typename T>
bool Array<T>::search(const T& data)
{
	if (this->size == 0)
	{
		return false;
	}

	for (size_t i = 0; i < this->size; i++)
	{
		if (this->head[i] == data)
		{
			return true;
		}
	}

	return false;
}

template <typename T>
bool Array<T>::removeFront()
{
	//	Sprawdzenie czy w tablicy znajduj¹ siê jakiekolwiek dane.
	if (this->head == nullptr)
	{
		return false;
	}

	T* newHead = nullptr;

	//	Skopiowanie danych.
	if (this->size > 1)
	{
		newHead = new T[size - 1];
		for (size_t i = 1; i < this->size; i++)
		{
			newHead[i - 1] = this->head[i];
		}
	}

	delete[] this->head;
	this->size--;
	this->head = newHead;
	return true;
}

template <typename T>
bool Array<T>::removeBack()
{
	//	Sprawdzenie czy w tablicy znajduj¹ siê jakiekolwiek dane.
	if (this->head == nullptr)
	{
		return false;
	}

	T* newHead = nullptr;
	this->size--;

	// Skopiowanie danych.
	if (this->size >= 1)
	{
		newHead = new T[size];
		for (size_t i = 0; i < this->size; i++)
		{
			newHead[i] = this->head[i];
		}
	}

	delete[] this->head;
	this->head = newHead;
	return true;
}

template <typename T>
bool Array<T>::removeAt(const size_t& index)
{
	//	Sprawdzenie czy indeks jest poprawny.
	if (index >= this->size)
	{
		return false;
	}

	T* newHead = nullptr;

	//	Skopiowanie danych.
	if (this->size > 1)
	{
		newHead = new T[size - 1];

		//	Skopiowanie elementów znajduj¹cych siê przed konkretnym indeksem.
		for (size_t i = 0; i < index; i++)
		{
			newHead[i] = this->head[i];
		}

		//	Skopiowanie elementów znajduj¹cych siê po konkretnym indeksem.
		for (size_t i = index + 1; i < size; i++)
		{
			newHead[i - 1] = this->head[i];
		}
	}

	delete[] this->head;
	this->size--;
	this->head = newHead;
	return true;
}

template <typename T>
void Array<T>::print(std::ostream& out)
{
	if (this->size > 0 && this->head != nullptr)
	{
		for (size_t i = 0; i < this->size; i++)
		{
			out << i << "> " << this->head[i] << std::endl;
		}
		return;
	}
	out << "Data structure is empty" << std::endl;
}

template <typename T>
size_t Array<T>::getSize()
{
	return this->size;
}

//	Jedyny typ danych przydatny w tym projekcie.
template class Array<PathEdge>;