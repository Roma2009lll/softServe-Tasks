#pragma once

#include<iostream>
#include<stdexcept>
#include<type_traits>
#include<string>

class AnyType 
{
public:
	enum class Datatype
	{
		EMPTY=0,
		INT=1,
		FLOAT=2,
		DOUBLE=3,
		CHAR=4,
		BOOL=5
	};
private:
	union Storage
	{
		int int_val;
		double double_val;
		bool bool_val;
		char char_val;
		float float_val;

		Storage() :int_val(0) {}
	};
	Storage storage;
	Datatype cur_type;
public:

	AnyType() {
		cur_type = Datatype::EMPTY;
	}
	
	template<typename T>
	AnyType(T val)
	{
		if constexpr (std::is_same_v < T, int>)
		{
			cur_type = Datatype::INT;
			storage.int_val = val;
		}
		else if constexpr (std::is_same_v < T, float>)
		{
			cur_type = Datatype::FLOAT;
			storage.float_val = val;
		}
		else if constexpr (std::is_same_v < T, double>)
		{
			cur_type = Datatype::DOUBLE;
			storage.double_val = val;
		}
		else if constexpr (std::is_same_v < T, char>)
		{
			cur_type = Datatype::CHAR;
			storage.char_val = val;
		}
		else if constexpr (std::is_same_v < T, bool>)
		{
			cur_type = Datatype::BOOL;
			storage.bool_val = val;
		}else
		{
			throw std::invalid_argument("Unsoported data type\n");
		}
	}

	template<typename T>
	AnyType& operator=(T val)
	{
		if constexpr (std::is_same_v < T, int>)
		{
			cur_type = Datatype::INT;
			storage.int_val = val;
		}
		else if constexpr (std::is_same_v < T, float>)
		{
			cur_type = Datatype::FLOAT;
			storage.float_val = val;
		}
		else if constexpr (std::is_same_v < T, double>)
		{
			cur_type = Datatype::DOUBLE;
			storage.double_val = val;
		}
		else if constexpr (std::is_same_v < T, char>)
		{
			cur_type = Datatype::CHAR;
			storage.char_val = val;
		}
		else if constexpr (std::is_same_v < T, bool>)
		{
			cur_type = Datatype::BOOL;
			storage.bool_val = val;
		}
		else
		{
			throw std::invalid_argument("Unsoported data type\n");
		}
		return *this;
	}

	AnyType(const AnyType& another) = default;

	AnyType(AnyType&& another) noexcept = default;

	AnyType& operator=(const AnyType& other) = default;

	AnyType& operator=(AnyType&& other) noexcept = default;

	~AnyType() = default;

	void Swap(AnyType& other) noexcept
	{
		std::swap(storage, other.storage);
		std::swap(cur_type, other.cur_type);
	}

	Datatype GetType() const
	{
		return this->cur_type;
	}

	std::string_view GetTypeAsStirng() const
	{
		int type = static_cast<int>(this->GetType());
		static const char* type_arr[] = 
		{
			"empty",
			"int",
			"float",
			"double",
			"char",
			"bool"
		};
		return std::string_view(type_arr[type]);
	}

	template<typename T>
	T GetVal() const 
	{
		if constexpr (std::is_same_v<T, int>)
		{
			if (this->cur_type!=Datatype::INT)
			{
				throw std::runtime_error("Incorect type\n");
			}
			return this->storage.int_val;
		}
		else if constexpr (std::is_same_v < T, float>)
		{
			if (this->cur_type != Datatype::FLOAT)
			{
				throw std::runtime_error("Incorect type\n");
			}
			return this->storage.float_val;
		}
		else if constexpr (std::is_same_v < T, double>)
		{
			if (this->cur_type != Datatype::DOUBLE)
			{
				throw std::runtime_error("Incorect type\n");
			}
			return this->storage.double_val;
		}
		else if constexpr (std::is_same_v < T, char>)
		{
			if (this->cur_type != Datatype::CHAR)
			{
				throw std::runtime_error("Incorect type\n");
			}
			return this->storage.char_val;
		}
		else if constexpr (std::is_same_v < T, bool>)
		{
			if (this->cur_type != Datatype::BOOL)
			{
				throw std::runtime_error("Incorect type\n");
			}
			return this->storage.bool_val;
		}
		else
		{
			throw std::invalid_argument("Unsoported data type\n");
		}
	}

	int ToInt() const 
	{ 
		return GetVal<int>(); 
	}

	double ToDouble() const 
	{
		return GetVal<double>(); 
	}

	float ToFloat() const 
	{ 
		return GetVal<float>();
	}

	char ToChar() const 
	{ 
		return GetVal<char>(); 
	}

	bool ToBool() const 
	{ 
		return GetVal<bool>();
	}

	void Destroy()
	{
		cur_type = Datatype::EMPTY;
	}

};
