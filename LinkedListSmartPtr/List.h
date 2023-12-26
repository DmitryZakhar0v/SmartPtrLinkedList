#pragma once
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

template<typename T>
class Node;

template<typename T>
class List;

/**
* @brief Оператор вывода
* @param os Поток вывода
* @param list Список для вывода
* @return Поток вывода с информацией списка
*/
template<typename T>
std::ostream& operator<< (std::ostream& os, const List<T>& list);

/**
@brief Оператор равенства
@param rha Первый список для сравнения
@param lha Второй список для сравнения
@return true - если равны, иначе false
*/
template<typename T>
bool operator==(const List<T>& rha, const List<T>& lha) noexcept;

/**
@brief Оператор неравенства
@param rha Первый список для сравнения
@param lha Второй список для сравнения
@return true - если неравны, иначе false
*/
template<typename T>
bool operator!=(const List<T>& rha, const List<T>& lha) noexcept;


/*
@brief Класс, описывающий линейный односвязный список
*/
template<typename T>
class List
{
public:

	/*
	* @brief Создает пустой объект лжносвязного списка
	*/
	List();

	/*
	* @brief Создает список по элементам пользователя
	* @param list Элементы пользователя
	*/
	List(const std::initializer_list<T> list);

	/*
	* @brief Очищает список
	*/
	void clear();

	/*
	* @brief Преобразует список в строку
	* @return Строка, созданная по списку
	*/
	std::string to_string() const noexcept;

	/*
	* @brief Добавления элемента в список
	* @param value Элемент, который надо добавить
	*/
	void push(const T& value);

	/*
	* @brief Удаление элемента из списка
	*/
	void pop();

	/*
	* @brief Найти элемент в списке
	* @return true - если есть, иначе false
	*/
	bool find(const T& item);

	/*
	* @brief Проверка наличия элементов в списке
	* @return true - есть элементы, иначе false
	*/
	bool has_elements() const noexcept;

	/*
	* @brief Проверка отсутствия элементов в списке
	* @return true - нет элементов, иначе false
	*/
	bool is_empty() const noexcept;

	/*
	* @brief Оператор копирования
	* @param list Список для копирования
	* @return Скопированный List
	*/
	List<T>& operator=(const List<T>& list);

	/*
	* @brief Оператор перемещения
	* @param list Список для перемещения
	* @return Перемещенный List
	*/
	List<T>& operator=(List<T>&& list) noexcept;

	/*
	* @brief Конструктор копирования
	* @param list Список для копирования
	*/
	List(const List<T>& list);

	/*
	* @brief Конструктор перемещения
	* @param list Список для перемещения
	*/
	List(List<T>&& list) noexcept;

private:

	/*
	* @brief Класс, описывабщий элемент списка
	*/
	template<typename T>
	class Node
	{
	public:
		/*
		@brief  Создает элемент списка
		@param value Значение элемента
		@param next_node Следующий элемент списка
		*/
		Node(const T& value)
			:value{ value }, next_node{ nullptr }{};

		std::unique_ptr<Node<T>> next_node;
		T value;
	};

	std::unique_ptr<Node<T>> head;

};


template<typename T>
inline List<T>::List()
	:head{ nullptr }
{
}

template<typename T>
inline List<T>::List(const std::initializer_list<T> list)
	: head{ nullptr }
{
	std::vector<int> temp{};
	for (auto item : list)
	{
		temp.insert(temp.begin(), item);
	}
	for (size_t i = 0; i < temp.size(); i++)
	{
		this->push(temp[i]);
	}
}

template<typename T>
inline void List<T>::clear()
{
	this->head = nullptr;
}


template<typename T>
inline std::string List<T>::to_string() const noexcept
{
	std::stringstream result_string;
	result_string << "[ ";
	auto curr = this->head.get();
	while (curr != nullptr)
	{
		result_string << curr->value << " ";
		curr = curr->next_node.get();
	}
	result_string << "]";
	return result_string.str();
}

template<typename T>
inline void List<T>::push(const T& value)
{
	std::unique_ptr<Node<T>> element(new Node<T>(value));
	if (this->has_elements())
	{
		element->next_node = std::move(this->head);
		this->head = std::move(element);
	}
	else
	{
		this->head = std::move(element);
	}

}

template<typename T>
inline void List<T>::pop()
{
	if (this->has_elements())
	{
		std::unique_ptr<Node<T>> temp = std::move(head);
		this->head = std::move(temp->next_node);
	}
}

template<typename T>
inline bool List<T>::find(const T& item)
{
	auto curr = this->head.get();
	while (curr != nullptr)
	{
		if (curr->value == item)
		{
			return true;
		}
		curr = curr->next_node.get();
	}
	return false;
}

template<typename T>
inline bool List<T>::has_elements() const noexcept
{
	return !(this->is_empty());
}

template<typename T>
inline bool List<T>::is_empty() const noexcept
{
	return this->head == nullptr;
}

template<typename T>
inline List<T>& List<T>::operator=(const List<T>& list)
{
	if (*this != list)
	{
		List temp{ list };
		std::swap(this->head, temp.head);
	}
	return *this;
}

template<typename T>
inline List<T>& List<T>::operator=(List<T>&& list) noexcept
{
	if (*this != list)
	{
		std::swap(this->head, list.head);
	}
	return *this;
}

template<typename T>
inline List<T>::List(const List<T>& list)
	:head{ nullptr }
{
	List<T> temp;
	std::vector<T> invetred;
	for (auto node = list.head.get(); node != nullptr; node = node->next_node.get())
	{
		invetred.insert(invetred.begin(), node->value);
	}

	for (size_t i = 0; i < invetred.size(); i++)
	{
		temp.push(invetred[i]);
	}
	std::swap(this->head, temp.head);
}


template<typename T>
inline List<T>::List(List<T>&& list) noexcept
	:head{ nullptr }
{
	std::swap(this->head, list.head);
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const List<T>& list)
{
	return os << list.to_string();
}

template<typename T>
inline bool operator==(const List<T>& rha, const List<T>& lha) noexcept
{
	if (&lha == &rha)
	{
		return true;
	}
	return rha.to_string() == lha.to_string();
}

template<typename T>
inline bool operator!=(const List<T>& rha, const List<T>& lha) noexcept
{
	return !(rha.to_string() == lha.to_string());
}