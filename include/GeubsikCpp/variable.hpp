#ifndef GEUBSIKCPP_HEADER_VARIABLE_HPP
#define GEUBSIKCPP_HEADER_VARIABLE_HPP

#include <string>
#include <string_view>
#include <variant>

namespace gs
{
	class function;

	enum class variable_type
	{
		undefined,
		number,
		string,
		function,
	};

	class variable final
	{
	public:
		variable() noexcept = default;
		explicit variable(std::string name) noexcept;
		variable(const std::variant<std::monostate, double, std::string, const gs::function*>& value);
		variable(std::variant<std::monostate, double, std::string, const gs::function*>&& value) noexcept;
		variable(std::string name, const std::variant<std::monostate, double, std::string, const gs::function*>& value);
		variable(std::string name, std::variant<std::monostate, double, std::string, const gs::function*>&& value) noexcept;
		variable(const variable& variable);
		variable(variable&& variable) noexcept;
		~variable() = default;

	public:
		variable& operator=(const variable& variable);
		variable& operator=(variable&& variable) noexcept;
		
	public:
		int compare(const variable& variable) const noexcept;
		bool is_undefined() const noexcept;

	public:
		variable_type type() const noexcept;
		std::string_view name() const noexcept;

		double number() const noexcept;
		double& number() noexcept;
		std::string_view string() const noexcept;
		std::string& string() noexcept;
		const gs::function* function() const noexcept;
		const gs::function*& function() noexcept;

	private:
		std::variant<std::monostate, double, std::string, const gs::function*> data_;
		std::string name_;

	private:
		static int compare_number_(double a, double b) noexcept;
		static int compare_string_(const std::string_view& a, const std::string_view& b) noexcept;
		static int compare_function_(const gs::function* a, const gs::function* b) noexcept;
		static int compare_number_string_(double a, const std::string& b) noexcept;
		static int compare_string_number_(const std::string& a, double b) noexcept;
	};
}

#endif