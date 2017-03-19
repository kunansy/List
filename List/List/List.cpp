#include "List.h"

namespace SLL
{
	List::List()
	{
		begin = NULL;
	}
	List::List(const List& v)
	{
		begin = v.begin;
	}
	List::~List()
	{
		if (begin == NULL)
			return;

		list* p = begin;
		list* t;

		while (p)
		{
			t = p;
			p = p->next;
			delete t;
		}
		begin = NULL;
	}

	List& List::Insert(const size_t a)
	{
		list* ins = new list;
		ins->a.key = a;
		ins->next = NULL;

		list* t = begin;
		if (begin == NULL)
		{
			begin = ins;
			Indexation();
			return *this;
		}

		if (ins->a.key <= t->a.key)
		{
			ins->next = t;
			begin = ins;
			Indexation();
			return *this;
		}
		list* t1 = t->next;
		while (t != NULL)
		{
			if (t->next == NULL)
			{
				t->next = ins;
				Indexation();
				return *this;
			}

			if (ins->a.key >= t->a.key && ins->a.key <= t1->a.key)
			{
				t->next = ins;
				ins->next = t1;
				Indexation();
				return *this;
			}

			t = t->next;
			t1 = t->next;
		}
	}
	List& List::Delete(const size_t a)
	{
		if (begin == NULL)
			throw std::runtime_error(BAD_BEGIN);
		list* t = begin;

		if (t->a.key == a)
		{
			begin = t->next;
			delete t;
			Indexation();
			return *this;
		}
		list*  t1 = t->next;
		while (t1 != NULL)
		{
			if (t1->a.key == a)
			{
				t->next = t1->next;
				delete t1;
				Indexation();
				return *this;
			}
			t = t1;
			t1 = t1->next;
		}
		throw std::runtime_error("Element not found");
	}
	int List::IndexDelete(const int value)
	{
		if (begin == NULL)
			throw std::runtime_error(BAD_BEGIN);
		
		int temp = 0;

		list* t = begin;
		list*  t1 = t->next;

		if (t->a.index == value)
		{
			temp = t->a.key;
			begin = t->next;
			delete t;
			Indexation();
			return temp;
		}

		while (t1 != NULL)
		{
			if (t1->a.index == value)
			{
				temp = t1->a.key;
				t->next = t1->next;
				delete t1;
				Indexation();
				return temp;
			}
			t = t1;
			t1 = t1->next;
		}
		throw std::runtime_error("Element not found");
	}
	List& List::push_back(const size_t v)
	{
		list* ins = new list;
		ins->a.key = v;
		ins->next = NULL;

		if (begin == NULL)
		{
			begin = ins;
			Indexation();
			return *this;
		}

		list* temp = begin;

		while (1)
		{
			if (temp->next == NULL)
			{
				temp->next = ins;
				Indexation();
				return *this;
			}
			temp = temp->next;
		}
		
	}
	List& List::push_front(const size_t v)
	{
		list* ins = new list;
		ins->a.key = v;
		ins->next = begin;
		begin = ins;
		Indexation();
		return *this;
	}
	size_t List::size() const
	{
		if (begin == NULL)
			return 0;
		list* temp = begin;
		size_t result = 0;
		while (temp)
		{
			result++;
			temp = temp->next;
		}
		return result;
	}

	void List::Output_with_file(const std::string& FileName)const
	{
		if (begin == NULL)
			throw std::runtime_error(BAD_BEGIN);

		std::ofstream fout;
		list* print = begin;

		fout.open(FileName);

		fout << size() << std::endl;

		for (size_t i(0); i < size() - 1; i++)
		{
			fout << print->a.key << std::endl;
			print = print->next;
		}
		fout << print->a.key;

		std::cout << "������ ������� ������� � ����!" << std::endl;
	}
	void Input_with_file(List& result,const std::string& FileName)
	{
		std::ifstream fin;
		fin.open(FileName);
		
		if (fin.is_open() != true)
			throw std::runtime_error("���� �� ��������");

		int List_size;

		fin >> List_size;
		
		size_t AddValue = 0;

		for (int i(0); i < List_size; i++)
		{
			fin >> AddValue;
			result.push_back(AddValue);
		}
	
		result.Indexation();
	}
	size_t List::KeyFind(const size_t key)
	{
		for (size_t i(1); i <= size(); i++)
			if ((*this)[i].key == key)
				return (*this)[i].index;
		return 0;
	}

	List& List::KeySort()
	{
		list* temp = begin;
		A* Arr = Array();

		for (size_t i(0); i < size(); i++)
			for (size_t j(0); j < i; j++)
				if (Arr[i].key > Arr[j].key)
					std::swap(Arr[i], Arr[j]);

		for (size_t i(0); i < size(); i++)
		{
			temp->a = Arr[i];
			temp = temp->next;
		}
		return *this;
	}
	List& List::keySortMin()
	{
		list* temp = begin;
		A* Arr = Array();

		for (size_t i(0); i < size(); i++)
			for (size_t j(0); j < i; j++)
				if (Arr[i].key < Arr[j].key)
					std::swap(Arr[i], Arr[j]);

		for (size_t i(0); i < size(); i++)
		{
			temp->a = Arr[i];
			temp = temp->next;
		}
		return *this;
	}
	List& List::IndexSort()
	{
		list* temp = begin;
		A* Arr = Array();

		for (size_t i(0); i < size(); i++)
			for (size_t j(0); j < i; j++)
				if (Arr[i].index > Arr[j].index)
					std::swap(Arr[i], Arr[j]);

		for (size_t i(0); i < size(); i++)
		{
			temp->a = Arr[i];
			temp = temp->next;
		}
		return *this;
	}
	List& List::IndexSortMin()
	{
		list* temp = begin;
		A* Arr = Array();

		for (size_t i(0); i < size(); i++)
			for (size_t j(0); j < i; j++)
				if (Arr[i].index < Arr[j].index)
					std::swap(Arr[i], Arr[j]);

		for (size_t i(0); i < size(); i++)
		{
			temp->a = Arr[i];
			temp = temp->next;
		}
		return *this;
	}

	List& List::set_key(std::string str)
	{
		if (status.Encpt_status == false)
		{
			status.key = str;
			return *this;
		}

		if (status.Encpt_status == true)
		{
			Encryption(*this);
			status.Encpt_status = false;
			status.key = str;
			return *this;
		}
	}
	void Encryption(List& v)
	{
		if (v.begin == NULL)
			throw std::runtime_error("Bad begin");

		if (v.status.key == "")
			throw std::runtime_error("���� ���������� ����!");

		List::list* temp = v.begin;

		if (v.status.Encpt_status == true)
		{
			while (temp != NULL)
			{
				for (size_t i(0); i < v.status.key.size(); i++)
					temp->a.key ^= v.status.key[i];
				temp = temp->next;
			}
			v.status.Encpt_status = false;
		}

		while (temp != NULL)
		{
			for (size_t i(0); i < v.status.key.size(); i++)
				temp->a.key ^= v.status.key[i];
			temp = temp->next;
		}
		v.status.Encpt_status = true;
	}
	
	double List::averege_value() const
	{
		if (begin == NULL)
			return 0;

		list* temp = begin;

		double i = 0;

		while (temp != NULL)
		{
			i += (double)temp->a.key;
			temp = temp->next;
		}

		return i / size();
	}
	ld List::GeometryMean() const
	{
		if (begin == NULL)
			return 0;

		list* temp = begin;
		long double i = 1;

		while (temp != NULL)
		{
			i *= (double)temp->a.key;
			temp = temp->next;
		}

		return sqrt(i);
	}
	int List::maximum_value()const
	{
		if (begin == NULL)
			return 0;

		list* temp = begin;
		size_t result = 0;
		while (temp != NULL)
		{
			if ((size_t)temp->a.key >= result)
			{
				result = temp->a.key;
			}
			temp = temp->next;
		}
		return result;
	}
	int List::minimum_value()const
	{
		if (begin == NULL)
			return 0;

		list* temp = begin;
		size_t result = LONG_MAX;

		while (temp != NULL)
		{
			if ((size_t)temp->a.key <= result)
			{
				result = temp->a.key;
			}
			temp = temp->next;
		}
		if (result == LONG_MAX)
			result = 0;
		return result;
	}
	void List::Indexation()
	{
		if (begin == NULL)
			return;
		list* temp = begin;

		for (size_t i(0); i < size(); i++)
		{
			temp->a.index = (i + 1);
			temp = temp->next;
		}
	}
	List::A* List::Array()
	{
		A* result = new A[size()];
		list* temp = begin;

		for (size_t i(0); i < size(); i++)
		{
			result[i] = temp->a;
			temp = temp->next;
		}
		return result;
	}
	
	std::ostream& operator<<(std::ostream& os,const  List& v)
	{
		SLL::List::list* print = v.begin;

		while (print != NULL)
		{
			os << print->a.key << " -> ";
			print = print->next;
		}
		os << "NULL" << std::endl;

		print = v.begin;

		while (print != NULL)
		{
			os << print->a.index << " -> ";
			print = print->next;
		}
		os << "NULL" << std::endl;

		os << std::endl;
		os.setf(std::ios_base::fixed, std::ios_base::floatfield);
		os.precision(0);

		os << "������� �������������� ������: " << v.averege_value() << std::endl;
		os << "������� �������������� ������: " << v.GeometryMean() << std::endl;
		os << "������������ �������� ������: " << v.maximum_value() << std::endl;
		os << "����������� �������� ������: " << v.minimum_value() << std::endl;
		os << std::endl;
		return os;
	}
	std::istream& operator>>(std::istream& os, List& v)
	{
		if (v.begin == NULL)
			return os;
		for (size_t i(0); i < v.size(); i++)
		{
			std::cout << "������� �������� " << i + 1 << " �������� ������: ";
			os >> v[i+1].key;
		}
		return os;
	}

	List::A& List::operator[](const size_t index) 
	{
		if (index > size() || index <= 0)
			throw std::runtime_error("������ ������� ������ ������\a");

		int temp = 1;
		list* ret = begin; // ������������ ��������� ���������

		for(;;)
		{
			if (temp == index)
			{
				return ret->a;
			}
			temp++;
			ret = ret->next;
		}
	}
	std::ostream& operator<<(std::ostream& os, List::A& v)
	{
		os << v.key << std::endl;
		return os;
	}

}
using namespace SLL;