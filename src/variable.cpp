#include <GeubsikCpp/variable.hpp>

#include <GeubsikCpp/function.hpp>

#include <cassert>
#include <new>
#include <utility>

namespace gs
{
	variable::variable(std::string name) noexcept
		: name_(std::move(name))
	{}
	variable::variable(const std::variant<std::monostate, double, std::string, const gs::function*>& value)
		: data_(value)
	{}
	variable::variable(std::variant<std::monostate, double, std::string, const gs::function*>&& value) noexcept
		: data_(std::move(value))
	{}
	variable::variable(std::string name, const std::variant<std::monostate, double, std::string, const gs::function*>& value)
		: name_(std::move(name)), data_(value)
	{}
	variable::variable(std::string name, std::variant<std::monostate, double, std::string, const gs::function*>&& value) noexcept
		: name_(std::move(name)), data_(std::move(value))
	{}
	variable::variable(const variable& variable)
		: data_(variable.data_)
	{}
	variable::variable(variable&& variable) noexcept
		: data_(std::move(variable.data_))
	{}

	variable& variable::operator=(const variable& variable)
	{
		data_ = variable.data_;
		return *this;
	}
	variable& variable::operator=(variable&& variable) noexcept
	{
		data_ = std::move(variable.data_);
		return *this;
	}

	int variable::compare(const variable& variable) const noexcept
	{
		const variable_type my_type = type();
		const variable_type other_type = variable.type();

		if (my_type == other_type)
		{
			switch (my_type)
			{
			case variable_type::undefined: return 0;
			case variable_type::number: return compare_number_(std::get<1>(data_), std::get<1>(variable.data_));
			case variable_type::string: return compare_string_(std::get<2>(data_), std::get<2>(variable.data_));
			case variable_type::function: return compare_function_(std::get<3>(data_), std::get<3>(variable.data_));
			default: assert(false);
			}
		}

		switch (my_type)
		{
		case variable_type::undefined: return 1;
		case variable_type::number:
			switch (other_type)
			{
			case variable_type::undefined: return -1;
			case variable_type::string: return compare_number_string_(std::get<1>(data_), std::get<2>(variable.data_));
			case variable_type::function: return -2;
			default: assert(false);
			}
		case variable_type::string:
			switch (other_type)
			{
			case variable_type::undefined: return -1;
			case variable_type::number: return compare_string_number_(std::get<2>(data_), std::get<1>(variable.data_));
			case variable_type::function: return -2;
			default: assert(false);
			}
		case variable_type::function:
			switch (other_type)
			{
			case variable_type::undefined: return -1;
			case variable_type::number:
			case variable_type::string: return -2;
			default: assert(false);
			}
		default: assert(false);
		}
	}
	bool variable::is_undefined() const noexcept
	{
		return type() == variable_type::undefined;
	}

	variable_type variable::type() const noexcept
	{
		return static_cast<variable_type>(data_.index());
	}
	std::string_view variable::name() const noexcept
	{
		return name_;
	}

	double variable::number() const noexcept
	{
		return std::get<1>(data_);
	}
	double& variable::number() noexcept
	{
		return std::get<1>(data_);
	}
	std::string_view variable::string() const noexcept
	{
		return std::get<2>(data_);
	}
	std::string& variable::string() noexcept
	{
		return std::get<2>(data_);
	}
	const function* variable::function() const noexcept
	{
		return std::get<3>(data_);
	}
	const function*& variable::function() noexcept
	{
		return std::get<3>(data_);
	}

	int variable::compare_number_(double a, double b) noexcept
	{
		if (a == b) return 0;
		else if (a > b) return -1;
		else return 1;
	}
	int variable::compare_string_(const std::string_view& a, const std::string_view& b) noexcept
	{
		if (a == b) return 0;
		else if (a > b) return -1;
		else return 1;
	}
	int variable::compare_function_(const gs::function* a, const gs::function* b) noexcept
	{
		if (!a && !b) return 0;
		else if (a && !b) return -1;
		else if (!a && b) return 1;

		if (a == b) return 0;
		else return compare_string_(a->name(), b->name());
	}
	int variable::compare_number_string_(double a, const std::string& b) noexcept
	{
		try
		{
			const double b_number = std::stod(b);
			return compare_number_(a, b_number);
		}
		catch (...)
		{
			return -2;
		}
	}
	int variable::compare_string_number_(const std::string& a, double b) noexcept
	{
		try
		{
			const std::string b_string = std::to_string(b);
			return compare_string_(a, b_string);
		}
		catch (...)
		{
			return -2;
		}
	}
}