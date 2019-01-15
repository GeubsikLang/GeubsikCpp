#ifndef GEUBSIKCPP_HEADER_COMMAND_HPP
#define GEUBSIKCPP_HEADER_COMMAND_HPP

#include <GeubsikCpp/variable.hpp>

#include <vector>

namespace gs
{
	enum class command_type
	{
		none,

		function_begin,
		function_end,
		function_call,
		function_return,
		stdfunc_printfs,
		stdfunc_printfsn,
		stdfunc_scanflf,
		stdfunc_scanfc,
		if_begin,
		if_elseif,
		if_else,
		if_end,
		variable_assign,
		variable_inc,
		variable_dec,
		while_begin,
		while_end,
		loop_break,
		loop_continue,
	};

	class command final
	{
	public:
		command() noexcept = default;
		command(command_type type, std::vector<variable> arguments);
		command(const command& command);
		command(command&& command) noexcept;
		~command() = default;

	public:
		command& operator=(const command& command);
		command& operator=(command&& command) noexcept;
		
	public:
		void clear() noexcept;
		bool empty() const noexcept;

	public:
		command_type type() const noexcept;
		const std::vector<variable>& arguments() const noexcept;

	private:
		command_type type_ = command_type::none;
		std::vector<variable> arguments_;
	};
}

#endif