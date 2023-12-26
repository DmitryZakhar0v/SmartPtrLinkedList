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
* @brief �������� ������
* @param os ����� ������
* @param list ������ ��� ������
* @return ����� ������ � ����������� ������
*/
template<typename T>
std::ostream& operator<< (std::ostream& os, const List<T>& list);

/**
@brief �������� ���������
@param rha ������ ������ ��� ���������
@param lha ������ ������ ��� ���������
@return true - ���� �����, ����� false
*/
template<typename T>
bool operator==(const List<T>& rha, const List<T>& lha) noexcept;

/**
@brief �������� �����������
@param rha ������ ������ ��� ���������
@param lha ������ ������ ��� ���������
@return true - ���� �������, ����� false
*/
template<typename T>
bool operator!=(const List<T>& rha, const List<T>& lha) noexcept;


/*
@brief �����, ����������� �������� ����������� ������
*/
template<typename T>
class List
{
public:

	/*
	* @brief ������� ������ ������ ������������ ������
	*/
	List();

	/*
	* @brief ������� ������ �� ��������� ������������
	* @param list �������� ������������
	*/
	List(const std::initializer_list<T> list);

	/*
	* @brief ������� ������
	*/
	void clear();

	/*
	* @brief ����������� ������ � ������
	* @return ������, ��������� �� ������
	*/
	std::string to_string() const noexcept;

	/*
	* @brief ���������� �������� � ������
	* @param value �������, ������� ���� ��������
	*/
	void push(const T& value);

	/*
	* @brief �������� �������� �� ������
	*/
	void pop();

	/*
	* @brief ����� ������� � ������
	* @return true - ���� ����, ����� false
	*/
	bool find(const T& item);

	/*
	* @brief �������� ������� ��������� � ������
	* @return true - ���� ��������, ����� false
	*/
	bool has_elements() const noexcept;

	/*
	* @brief �������� ���������� ��������� � ������
	* @return true - ��� ���������, ����� false
	*/
	bool is_empty() const noexcept;

	/*
	* @brief �������� �����������
	* @param list ������ ��� �����������
	* @return ������������� List
	*/
	List<T>& operator=(const List<T>& list);

	/*
	* @brief �������� �����������
	* @param list ������ ��� �����������
	* @return ������������ List
	*/
	List<T>& operator=(List<T>&& list) noexcept;

	/*
	* @brief ����������� �����������
	* @param list ������ ��� �����������
	*/
	List(const List<T>& list);

	/*
	* @brief ����������� �����������
	* @param list ������ ��� �����������
	*/
	List(List<T>&& list) noexcept;

private:

	/*
	* @brief �����, ����������� ������� ������
	*/
	template<typename T>
	class Node
	{
	public:
		/*
		@brief  ������� ������� ������
		@param value �������� ��������
		@param next_node ��������� ������� ������
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