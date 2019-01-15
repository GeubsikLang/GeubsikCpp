#include <GeubsikCpp/parser.hpp>

#include <cstddef>

namespace gs::parser
{
	namespace
	{
		std::string_view substr(const std::string_view& val, std::size_t i, std::size_t l)
		{
			if (i + l <= val.size()) return val.substr(i, l);
			else return "";
		}

		std::string parse_function_begin(const std::vector<std::string>& tokens, std::vector<command>& result)
		{
			if (tokens.size() != 4 ||
				tokens[1] != u8"ㄹㅇ" ||
				substr(tokens[2], tokens[2].size() - 3, 3) != u8"인" ||
				tokens[3] != u8"부분ㅋㅋ") return "올바르지 않은 함수 선언문입니다.";
			
			const std::string function_name(substr(tokens[2], 0, tokens[2].size() - 3));
			result.push_back(command(command_type::function_begin, { std::move(function_name) }));

			return "";
		}
		std::string parse_function_end(const std::vector<std::string>& tokens, std::vector<command>& result)
		{
			if (tokens.size() != 4 ||
				tokens[1] != u8"ㅇㅈ하시죠?" ||
				tokens[2] != u8"네" ||
				tokens[3] != u8"그렇습니다") return "올바르지 않은 함수 선언문입니다.";

			result.push_back(command(command_type::function_end, {}));

			return "";
		}
		std::string parse_function_call(const std::vector<std::string>& tokens, std::vector<command>& result)
		{
			if (tokens.size() < 6 ||
				tokens[1] != u8"지리고" ||
				tokens[2] != u8"렛잇고" ||
				substr(tokens[3], tokens[3].size() - 3, 3) != u8"고" ||
				tokens[tokens.size() - 2] != u8"미쳐버린" ||
				tokens[tokens.size() - 1] != u8"부분") return "올바르지 않은 함수 호출문입니다.";

			const std::string function_name(substr(tokens[3], 0, tokens[3].size() - 3));
			std::vector<std::string> arguments;

			std::string prev_token;

			for (std::size_t i = 4; i < tokens.size() - 2; ++i)
			{
				const std::string_view splited = tokens[i].size() >= 3 ? substr(tokens[i], tokens[i].size() - 3, 3) : tokens[i];

				if (splited != u8"고")
				{
					prev_token += tokens[i] + ' ';
					continue;
				}

				arguments.push_back(prev_token + std::string(substr(tokens[i], 0, tokens[i].size() - 3)));
				prev_token.clear();
			}

			if (!prev_token.empty()) return "올바르지 않은 함수 호출문입니다.";

			result.push_back(command(command_type::function_call, std::move(arguments)));

			return "";
		}
		/*std::string parse_function_call(const std::vector<std::string>& tokens, std::vector<command>& result)
		{

		}
		std::string parse_stdfunc_printf(const std::vector<std::string>& tokens, std::vector<command>& result)
		{

		}
		std::string parse_if_else(const std::vector<std::string>& tokens, std::vector<command>& result)
		{

		}
		std::string parse_return(const std::vector<std::string>& tokens, std::vector<command>& result)
		{

		}
		std::string parse_break(const std::vector<std::string>& tokens, std::vector<command>& result)
		{

		}
		std::string parse_continue(const std::vector<std::string>& tokens, std::vector<command>& result)
		{

		}*/
	}

	std::vector<std::vector<std::string>> tokenize(const std::string_view& code)
	{
		std::vector<std::vector<std::string>> result;
		std::vector<std::string>* line = &result.emplace_back();

		std::size_t begin_index = 0;
		std::size_t length = 0;

		for (std::size_t i = 0; i < code.size(); ++i)
		{
			if (code[i] == ' ' || code[i] == '\t' || code[i] == '\n')
			{
				if (length)
				{
					line->push_back(std::string(code.substr(begin_index, length)));
				}

				begin_index = i + 1;
				length = 0;

				if (code[i] == '\n')
				{
					line = &result.emplace_back();
				}
			}
			else ++length;
		}

		if (length)
		{
			line->push_back(std::string(code.substr(begin_index, length)));
		}

		return result;
	}
	std::vector<command> parse(const std::vector<std::vector<std::string>>& tokens)
	{
		std::vector<command> result;
		std::vector<std::string> error_messages;
#define add_error() error_messages.push_back(u8"줄 " + std::to_string(line_n) + u8": " + error_message)

		const std::string empty_message;
		std::string error_message;
#define check_error(func_name) ((error_message = func_name(line, result)), !error_message.empty())

		std::size_t line_n = 0;
		for (const std::vector<std::string>& line : tokens)
		{
			++line_n;

			if (line[0] == u8"이거" && check_error(parse_function_begin)) add_error();
			else if (line[0] == u8"판사님도" && check_error(parse_function_end)) add_error();
			else if (line[0] == u8"오지고" && check_error(parse_function_call)) add_error();
			/*else if (line[0] == u8"오지고" && check_error(parse_function_call)) add_error();
			else if (line[0] == u8"앙" && check_error(parse_stdfunc_printf)) add_error();
			else if (line[0] == u8"그런데" && check_error(parse_if_else)) add_error();
			else if (line[0] == u8"응" && check_error(parse_return)) add_error();
			else if (substr(line[0], 0, 3) == u8"아" && check_error(parse_break)) add_error();
			else if (substr(line[0], 0, 6) == u8"뭐지" && check_error(parse_continue)) add_error();*/
		}

		return result;
	}
}