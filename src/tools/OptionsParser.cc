/**
 * \file
 * \date December 17, 2020
 * \author JP
 * \brief Option and OptionsParser classes definitions
 */

#include <tools/OptionsParser.hh>

#include <algorithm>
#include <iomanip>
#include <iostream>

#include <tools/Debug.hh>



OptionsParser::OptionsParser(int ac, const char** av)
{
  // Build a copy of the forwarded argument vector
  for (int i = 0; i < ac; ++i)
  {
    _av.emplace_back(av[i]);
  }

  // Expecting at least the program name; The arguments count must be consistent
  const auto nb_args(_av.size());
  if ((nb_args == 0u) || static_cast<int> (nb_args) != ac)
  {
    // Should never happen
    throw ArgumentsException("Ill-formed arguments list.");
  }


  // Build the supported options list
  _supportedOptions.emplace(
    "help",
    Option("help",
           "Show this help",
           { "-h", "--help", "/h", "/?", "/help" },
           e_option_argument::NONE
    )
  );

  _supportedOptions.emplace(
    "version",
    Option("version",
           "Display " + _av[0] + " version",
           { "-v", "--version", "/v", "/version" },
           e_option_argument::NONE
    )
  );

  _supportedOptions.emplace(
    "random-seed",
    Option("random-seed",
           "Initialize the random generator with the given seed;"
           " --random-seed=123456789",
           { "", "--random-seed", "/random-seed" },
           e_option_argument::REQUIRED
    )
  );

  _supportedOptions.emplace(
    "fullscreen",
    Option("fullscreen",
           "Launch the binary in full screen",
           { "-f", "--fullscreen", "--full-screen", "/f", "/fullscreen" },
           e_option_argument::NONE
    )
  );
}



std::optional<const Option>
OptionsParser::operator[] (const std::string& name) const noexcept(true)
{
  const auto opt = _supportedOptions.at(name);
  if (opt.provided())
  {
    return opt;
  }

  return {};
}



void OptionsParser::parse()
{
  // Check the given arguments validity
  validArguments();

  // Fetch help or version option
  if (optionExists("help"))
  {
    displayHelp();
    throw ArgumentsHelpVersionException();
  }
  if (optionExists("version"))
  {
    displayVersion();
    throw ArgumentsHelpVersionException();
  }
}



void OptionsParser::displayVersion() const noexcept
{
  std::cout << _av[0] << ": version " << _version << '\n';
}



void OptionsParser::displayHelp() const noexcept
{
  displayVersion();
  std::cout << '\n'
            << "Usage:" << '\n';

  std::vector<std::string> lines;


  for (const auto& [name, opt]: _supportedOptions)
  {
    std::string line = "\n ";
    for (const auto& str: opt.aliases())
    {
      line.append(" ");
      line.append(str);
      if (str.empty())
      {
        line.append("  ");
      }
    }

    lines.emplace_back(line);
  }

  // Get the longest line in order to align correctly the descriptions
  auto max_length = 0ul;
  for (const auto& str: lines)
  {
    max_length = std::max(max_length, str.length());
  }

  // Print the descriptions
  auto i = 0u;
  for (const auto& [name, opt]: _supportedOptions)
  {
    auto line = lines[i++];
    std::cout << line
              << std::setfill(' ')
              << std::setw(static_cast<int> (max_length - line.length() + 1))
              << " "
              << opt.description();
  }

  std::cout << '\n' << std::endl;
}



void OptionsParser::validArguments()
{
  std::string error_msg; // Append any error to this variable

  // For each command line argument, check if it matches any option
  // +1: skip program name
  for (auto option = _av.begin() + 1; option != _av.end(); ++option)
  {
    // Extract any argument associated to the current option
    std::string argument;
    std::string op = *option;
    if (auto pos = option->find('='); pos != std::string::npos)
    {
      argument = option->substr(pos + 1);
      op = option->substr(0, pos);
    }

    // Search the provided option in the supported options list
    bool opt_valid = false;
    for (auto& [name, opt]: _supportedOptions)
    {
      auto flags = opt.aliases();
      if (std::find(flags.begin(), flags.end(), op) != flags.end())
      {
        opt.setProvided();
        opt.populateArguments(argument);
        opt_valid = true;
        if (opt.requiredArguments() == e_option_argument::REQUIRED)
        {
          if (argument.length() == 0u)
          {
            error_msg.append("\tOption " + op + " missing argument\n");
          }
        }
      }
    }

    if (!opt_valid)
    {
      error_msg.append("\tUnsupported option: " + op + '\n');
    }
  }

  if (!error_msg.empty())
  {
    displayHelp();
    throw ArgumentsException(error_msg);
  }
}



bool OptionsParser::optionExists(const std::string& option) const
{
  // Find the considered option in _supportedOptions ("help" for instance)
  for (const auto& [name, opt]: _supportedOptions)
  {
    if (opt.name() == option)
    {
      return opt.provided();
    }
  }

  // We should always find a given option
  ERROR("[IMPLEMENTATION ERROR] Unknown option", option);
  std::exit(1);
}



Option::Option(std::string name,
               std::string description,
               std::vector<std::string> aliases,
               const e_option_argument required_arguments)
  : _name(std::move(name))
  , _description(std::move(description))
  , _aliases(std::move(aliases))
  , _requiredArgs(required_arguments)
  , _provided(false)
{
}



void Option::populateArguments(const std::string& arguments)
{
  auto end_arg = arguments.find(',');
  decltype(end_arg) begin_arg = 0;
  auto args = arguments;
  while (end_arg != std::string::npos)
  {
    // Extract the current argument
    _arguments.emplace_back(args.substr(0, end_arg));

    // Omit the begining of the arguments string
    begin_arg = end_arg + 1;
    args = args.substr(begin_arg);
    end_arg = args.find(',');
  }

  // Handle last argument
  _arguments.emplace_back(args);


  // Debug: Options + arguments print
  // NOTICE("Option", _name, "arguments: ");
  // for (const auto& arg: _arguments)
  // {
  //   std::cout << arg << " ";
  // }
  // std::cout << '\n';
}
