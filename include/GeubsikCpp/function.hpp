#ifndef GEUBSIKCPP_HEADER_FUNCTION_HPP
#define GEUBSIKCPP_HEADER_FUNCTION_HPP

#include <GeubsikCpp/variable.hpp>

#include <functional>
#include <string>
#include <string_view>
#include <vector>

namespace gs
{
	enum class function_type
	{
		gsl_function,
		nat_function,
	};

	class function
	{
	public:
		function(const function&) = delete;
		virtual ~function() = default;

	protected:
		function(std::string name) noexcept;

	public:
		function& operator=(const function&) = delete;

	public:
		virtual function_type type() const noexcept = 0;
		virtual int parameter() const noexcept = 0;

	public:
		std::string_view name() const noexcept;

	private:
		std::string name_;
	};

	class gsl_function final : public function
	{
	public:
		gsl_function(std::string name, const std::string_view& code);
		gsl_function(const gsl_function&) = delete;
		virtual ~gsl_function() override = default;

	public:
		gsl_function& operator=(const gsl_function&) = delete;

	public:
		virtual function_type type() const noexcept override;
		virtual int parameter() const noexcept override;

	private:
		void parse_code_(const std::string_view& code);

	private:
		int parameter_;
	};

	class nat_function final : public function
	{
	public:
		nat_function(std::string name, int parameter, const std::function<variable(std::vector<variable>)>& function);
		nat_function(const nat_function&) = delete;
		virtual ~nat_function() override = default;

	public:
		nat_function& operator=(const nat_function&) = delete;

	public:
		virtual function_type type() const noexcept override;
		virtual int parameter() const noexcept override;

	private:
		int parameter_;
		std::function<variable(std::vector<variable>)> function_;
	};
}

#endif