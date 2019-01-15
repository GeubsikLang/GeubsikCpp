#include <GeubsikCpp/command.hpp>

#include <utility>

namespace gs
{
	command::command(command_type type, std::vector<variable> arguments)
		: type_(type), arguments_(std::move(arguments))
	{}
	command::command(const command& command)
		: type_(command.type_), arguments_(command.arguments_)
	{}
	command::command(command&& command) noexcept
		: type_(command.type_), arguments_(std::move(command.arguments_))
	{
		command.type_ = command_type::none;
	}

	command& command::operator=(const command& command)
	{
		type_ = command.type_;
		arguments_ = command.arguments_;
		return *this;
	}
	command& command::operator=(command&& command) noexcept
	{
		type_ = command.type_;
		arguments_ = std::move(command.arguments_);

		command.type_ = command_type::none;
		return *this;
	}

	void command::clear() noexcept
	{
		type_ = command_type::none;
		arguments_.clear();
	}
	bool command::empty() const noexcept
	{
		return type_ == command_type::none && arguments_.empty();
	}

	command_type command::type() const noexcept
	{
		return type_;
	}
	const std::vector<variable>& command::arguments() const noexcept
	{
		return arguments_;
	}
}