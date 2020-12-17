/**
 * \file
 * \date December 17, 2020
 * \author JP
 * \brief OptionsParser class declaration
 *   ArgumentsHelpVersionException ArgumentsException exception definition
 * \note Intern Option declaration and e_option_argument definition
 */

#ifndef OPTIONS_OPTIONS_PARSER_HH_
# define OPTIONS_OPTIONS_PARSER_HH_

# include <map>
# include <vector>
# include <utility>
# include <string>
# include <exception>
# include <optional>



/**
 * \class ArgumentsException
 * \brief Tool to parse options (from the command line),
 *   including the associated exceptions definitions
 * \warning Exception thrown if the provided are invalid
 */
class ArgumentsException final: public std::exception
{
public:
  /**
   * \brief Default constructor
   */
  ArgumentsException() = default;

  /**
   * \brief Constructor, initializing the exception message
   * \param msg Exception message (returned by exc.what())
   */
  explicit ArgumentsException(const std::string& msg)
    : _exc(msg)
  {
  }

  /**
   * \brief Standard exception what() override
   *   Displays the provided error message through the constructor
   */
  const char *what() const noexcept override final { return _exc.c_str(); }


private:
  /// Error message displayed by exc.what()
  std::string _exc = "Arguments exception";
};



/**
 * \class ArgumentsHelpVersionException
 * \brief Exception thrown if help or version argument were given
 */
class ArgumentsHelpVersionException: public std::exception
{
};



/**
 * \enum e_option_argument
 * \brief Provides flags if an argument is expected, optional, ...
 * \note For instance the --replay-file option expects a replay file
 */
enum class e_option_argument
{
  NONE = 0,
  OPTIONAL,
  REQUIRED,
};



/**
 * \class Option
 * \brief Represent command line options
 */
class Option
{
public:
  /**
   * \brief Deleted default constructor: Options attributes required
   */
  Option() = delete;

  /**
   * \brief Constructor
   * \param name Option name (used in the code)
   * \param description Option description to print in the help message
   * \param aliases Command line option invocation names
   * \param required_arguments Are arguments optional mandatory or forbidden ?
   */
  Option(std::string name,
         std::string description,
         std::vector<std::string> aliases,
         const e_option_argument required_arguments);

  /**
   * \brief _provided getter
   */
  auto provided() const { return _provided; }

  /**
   * \brief Sets the provided boolean to true
   * \note _provided is set to false in the constructor
   */
  void setProvided() { _provided = true; }

  /**
   * \brief Full option name getter ("help" for instance)
   * \return Option handy name
   */
  auto name() const { return _name; }

  /**
   * \brief Command line aliases getter
   * \return Option aliases list
   */
  auto aliases() const { return _aliases; }

  /**
   * \brief Description getter
   * \return Option description
   */
  auto description() const { return _description; }

  /**
   * \brief Argument status getter
   * \return Wether the option expects an argument
   */
  auto requiredArguments() const { return _requiredArgs; }

  /**
   * \brief Arguments getter
   * \return Option's arguments list
   */
  auto arguments() const { return _arguments; }

  /**
   * \brief Append the given arguments to the arguments list
   * \note Split the arguments using the ',' delimiter
   */
  void populateArguments(const std::string& arguments);


private:
  const std::string _name; ///< Option handy name
  const std::string _description; ///< Option description, used in help
  const std::vector<std::string> _aliases; ///< Command line invocations
  const e_option_argument _requiredArgs; ///< Does the option takes arguments
  std::vector<std::string> _arguments; ///< Option arguments (--opt=arg1,arg2)
  bool _provided; ///< Was the option provided on the command line
};



/**
 * \class OptionsParser
 * \brief Parses the command line arguments
 * \note Options must be preceded by a OPTIONS_DELIMITER
 */
class OptionsParser
{
public:
  /**
   * \brief Disabled default constructor as the argument vector is required
   */
  OptionsParser() = delete;

  /**
   * \brief Disabled copy constructor.
   *   There's (apparently) no good reason to need it
   */
  OptionsParser(const OptionsParser&) = delete;

  /**
   * \brief Constructor.
   *   Builds the iterable vector of options from the command line options
   * \param ac Argument count
   * \param av Argument vector (C-style)
   * \warning The argument vector must contain ac entries (throws otherwise)
   * \note This parameters should be directly forwarded from the main
   * \note Throws if no arguments is provided (ac == 0 or av empty)
   */
  OptionsParser(int ac, const char** av);


  /**
   * \brief Parse the options list, checking the arguments validity
   * \note Throws if the help or version is requested (-h --help -v --version)
   * \note Throws if the arguments are invalid (unrecognized option)
   */
  void parse();

  /**
   * \brief Check the existence of a given option
   * \param option Check if this specific option was provided
   * \warning Aborts the execution if the provided option is not referenced
   * \return true if the option was provided, false otherwise
   */
  bool optionExists(const std::string& option) const;

  /**
   * \brief Retrieve a given Option, by its name
   * \param name Option name to retrieve
   * \note throws std::out_of_range if the given option does not exist
   * \return The associated option, if any
   */
  std::optional<const Option>
  operator[] (const std::string& name) const noexcept(true);


private:
  /**
   * \brief Outputs the version
   */
  void displayVersion() const noexcept;

  /**
   * \brief Outputs the usage message
   */
  void displayHelp() const noexcept;

  /**
   * \brief Test the provided arguments validity
   *   Check if the arguments match supported options
   * \note throws if at least one argument is invalid
   * \note throws if the help or version option is provided
   */
  void validArguments();


  std::vector<std::string> _av; ///< mapping of the C arguments vector

  /// List of supported options
  std::map<std::string, Option> _supportedOptions;

  const std::string _version = "0.0.1"; ///< Program's version
};


#endif /* !OPTIONS_OPTIONS_PARSER_HH_ */
