#include <GeubsikCpp/function.hpp>

#include <utility>

namespace gs
{
	function::function(std::string name) noexcept
		: name_(std::move(name))
	{}

	std::string_view function::name() const noexcept
	{
		return name_;
	}
}

namespace gs
{
	gsl_function::gsl_function(std::string name, const std::string_view& code)
		: function(std::move(name))
	{
		parse_code_(code);
	}
	
	function_type gsl_function::type() const noexcept
	{
		return function_type::gsl_function;
	}
	int gsl_function::parameter() const noexcept
	{
		return parameter_;
	}

	void gsl_function::parse_code_(const std::string_view& code)
	{
		// TODO
	}
}

namespace gs
{
	nat_function::nat_function(std::string name, int parameter, const std::function<variable(std::vector<variable>)>& function)
		: function(std::move(name)), parameter_(parameter), function_(function)
	{}

	function_type nat_function::type() const noexcept
	{
		return function_type::nat_function;
	}
	int nat_function::parameter() const noexcept
	{
		return parameter_;
	}
}