#ifndef GEUBSIKCPP_HEADER_PARSER_HPP
#define GEUBSIKCPP_HEADER_PARSER_HPP

#include <GeubsikCpp/command.hpp>

#include <string>
#include <string_view>
#include <vector>

namespace gs::parser
{
	std::vector<std::vector<std::string>> tokenize(const std::string_view& code);
	std::vector<command> parse(const std::vector<std::vector<std::string>>& tokens);
}

#endif