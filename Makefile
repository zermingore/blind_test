bin = blind_test

SRC = lib/imgui/imgui.cpp \
      lib/imgui/imgui_draw.cpp \
      lib/imgui/imgui_widgets.cpp \
      lib/imgui-sfml/imgui-SFML.cpp \
      lib/imgui/imgui_demo.cpp \
      src/main.cc


INC=-Ilib/imgui -Ilib/imgui-sfml


CXX ?= g++



CXXFLAGS += -O0 -g3 -ggdb3 -DDEBUG

# CXXFLAGS += -Wall                              # Enable most warning messages
# CXXFLAGS += -Wextra                            # Print extra (possibly unwanted) warnings
# CXXFLAGS += -Wpedantic                         # Issue all the warnings demanded by strict ISO C and ISO C++
# CXXFLAGS += -Waggressive-loop-optimizations    # Warn if a loop with constant number of iterations triggers undefined behavior
# CXXFLAGS += -Wformat=2                         # Warn about printf/scanf/strftime/strfmon format string anomalies
# CXXFLAGS += -Wformat-contains-nul              # Warn about format strings that contain NUL bytes
# CXXFLAGS += -Wformat-extra-args                # Warn if passing too many arguments to a function for its format string
# CXXFLAGS += -Wformat-signedness                # Warn about sign differences with format functions
# CXXFLAGS += -Wformat-zero-length               # Warn about zero-length formats
# CXXFLAGS += -Warray-bounds=2                   # Warn if an array is accessed out of bounds # level 1 activated by -Wall (only with -O2); level2: also in structures
# CXXFLAGS += -Wattributes                       # Warn about inappropriate attribute usage
# CXXFLAGS += -Wbool-compare                     # Warn about boolean expression compared with an integer value different from true/false
# CXXFLAGS += -Wbuiltin-macro-redefined          # Warn when a built-in preprocessor macro is undefined or redefined
# CXXFLAGS += -Wcast-align                       # Warn about pointer casts which increase alignment
# CXXFLAGS += -Wcast-qual                        # Warn about casts which discard qualifiers
# CXXFLAGS += -Wconditionally-supported          # Warn for conditionally-supported constructs
# CXXFLAGS += -Wconversion                       # Warn for implicit type conversions that may change a value
# CXXFLAGS += -Wconversion-null                  # Warn for converting NULL from/to a non-pointer type
# CXXFLAGS += -Wctor-dtor-privacy                # Warn when all constructors and destructors are private
# CXXFLAGS += -Wdate-time                        # Warn about __TIME__, __DATE__ and __TIMESTAMP__ usage
# CXXFLAGS += -Wdelete-incomplete                # Warn when deleting a pointer to incomplete type
# CXXFLAGS += -Wdeprecated                       # Warn if a deprecated compiler feature, class, method, or field is used
# CXXFLAGS += -Wdeprecated-declarations          # Warn about uses of __attribute__((deprecated)) declarations
# CXXFLAGS += -Wdisabled-optimization            # Warn when an optimization pass is disabled
# CXXFLAGS += -Wdiv-by-zero                      # Warn about compile-time integer division by zero
# CXXFLAGS += -Wdouble-promotion                 # Warn about implicit conversions from "float" to "double"
# CXXFLAGS += -Wendif-labels                     # Warn about stray tokens after # elif and # endif
# CXXFLAGS += -Wfloat-equal                      # Warn if testing floating point numbers for equality
# CXXFLAGS += -Wfree-nonheap-object              # Warn when attempting to free a non-heap object
# CXXFLAGS += -Winherited-variadic-ctor          # Warn about C++11 inheriting constructors when the base has a variadic constructor
# CXXFLAGS += -Winit-self                        # Warn about variables which are initialized to themselves
# CXXFLAGS += -Wint-to-pointer-cast              # Warn when there is a cast to a pointer from an integer of a different size
# CXXFLAGS += -Winvalid-memory-model             # Warn when an atomic memory model parameter is known to be outside the valid range.
# CXXFLAGS += -Winvalid-offsetof                 # Warn about invalid uses of the "offsetof" macro
# CXXFLAGS += -Winvalid-pch                      # Warn about PCH files that are found but not used
# CXXFLAGS += -Wlarger-than=4096                 # Warn if an object is larger than <number> bytes
# CXXFLAGS += -Wliteral-suffix                   # Warn when a string or character literal is followed by a ud-suffix which does not begin with an underscore.
# CXXFLAGS += -Wlogical-not-parentheses          # Warn when logical not is used on the left hand side operand of a comparison
# CXXFLAGS += -Wlogical-op                       # Warn when a logical operator is suspiciously always evaluating to true or false
# CXXFLAGS += -Wlong-long                        # Do not warn about using "long long" when -pedantic
# CXXFLAGS += -Wmemset-transposed-args           # Warn about suspicious calls to memset where the third argument is constant literal zero and the second is not
# CXXFLAGS += -Wmissing-declarations             # Warn about global functions without previous declarations
# CXXFLAGS += -Wmissing-include-dirs             # Warn about user-specified include directories that do not exist
# CXXFLAGS += -Wnoexcept                         # Warn when a noexcept expression evaluates to false even though the expression can't actually throw
# CXXFLAGS += -Wnon-template-friend              # Warn when non-templatized friend functions are declared within a template
# CXXFLAGS += -Wnon-virtual-dtor                 # Warn about non-virtual destructors
# CXXFLAGS += -Wnormalized                       # Warn about non-normalised Unicode strings
# CXXFLAGS += -Wodr                              # Warn about some C++ One Definition Rule violations during link time optimization
# CXXFLAGS += -Wold-style-cast                   # Warn if a C-style cast is used in a program
# CXXFLAGS += -Woverflow                         # Warn about overflow in arithmetic expressions
# CXXFLAGS += -Woverloaded-virtual               # Warn about overloaded virtual function names
# CXXFLAGS += -Wpacked                           # Warn when the packed attribute has no effect on struct layout
# CXXFLAGS += -Wpacked-bitfield-compat           # Warn about packed bit-fields whose offset changed in GCC 4.4
# CXXFLAGS += -Wpmf-conversions                  # Warn when converting the type of pointers to member functions
# CXXFLAGS += -Wpragmas                          # Warn about misuses of pragmas
# CXXFLAGS += -Wredundant-decls                  # Warn about multiple declarations of the same object
# CXXFLAGS += -Wreturn-local-addr                # Warn about returning a pointer/reference to a local or temporary variable.
# CXXFLAGS += -Wshadow                           # Warn when one local variable shadows another
# CXXFLAGS += -Wshift-count-negative             # Warn if shift count is negative
# CXXFLAGS += -Wshift-count-overflow             # Warn if shift count >= width of type
# CXXFLAGS += -Wsign-promo                       # Warn when overload promotes from unsigned to signed
# CXXFLAGS += -Wsized-deallocation               # Warn about missing sized deallocation functions
# CXXFLAGS += -Wsizeof-array-argument            # Warn when sizeof is applied on a parameter declared as an array
# CXXFLAGS += -Wsizeof-pointer-memaccess         # Warn about suspicious length parameters to certain string functions if the argument uses sizeof
# CXXFLAGS += -Wstack-protector                  # Warn when not issuing stack smashing protection for some reason
# CXXFLAGS += -Wstrict-null-sentinel             # Warn about uncasted NULL used as sentinel
# CXXFLAGS += -Wstrict-overflow=5                # Warn about optimizations that assume that signed overflow is undefined # (5: overkill ?)
# CXXFLAGS += -Wsuggest-attribute=const          # Warn about functions which might be candidates for __attribute__((const))
# CXXFLAGS += -Wsuggest-attribute=format         # Warn about functions which might be candidates for format attributes
# CXXFLAGS += -Wsuggest-attribute=noreturn       # Warn about functions which might be candidates for __attribute__((noreturn))
# CXXFLAGS += -Wsuggest-attribute=pure           # Warn about functions which might be candidates for __attribute__((pure))
# CXXFLAGS += -Wsuggest-final-methods            # Warn about C++ virtual methods where adding final keyword would improve code quality
# CXXFLAGS += -Wsuggest-final-types              # Warn about C++ polymorphic types where adding final keyword would improve code quality
# CXXFLAGS += -Wsuggest-override                 # Suggest that the override keyword be used when the declaration of a virtual function overrides another.
# CXXFLAGS += -Wswitch-bool                      # Warn about switches with boolean controlling expression
# CXXFLAGS += -Wswitch-default                   # Warn about enumerated switches missing a "default:" statement
# CXXFLAGS += -Wsync-nand                        # Warn when __sync_fetch_and_nand and __sync_nand_and_fetch built-in functions are used
# CXXFLAGS += -Wtrampolines                      # Warn whenever a trampoline is generated
# CXXFLAGS += -Wunsafe-loop-optimizations        # Warn if the loop cannot be optimized due to nontrivial assumptions.
# CXXFLAGS += -Wunused-macros                    # Warn about macros defined in the main file that are not used
# CXXFLAGS += -Wuseless-cast                     # Warn about useless casts
# CXXFLAGS += -Wvarargs                          # Warn about questionable usage of the macros used to retrieve variable arguments
# CXXFLAGS += -Wvector-operation-performance     # Warn when a vector operation is compiled outside the SIMD
# CXXFLAGS += -Wvirtual-move-assign              # Warn if a virtual base has a non-trivial move assignment operator
# CXXFLAGS += -Wwrite-strings                    # In C++, nonzero means warn about deprecated conversion from string literals to 'char *'.
# CXXFLAGS += -Wzero-as-null-pointer-constant    # Warn when a literal '0' is used as null pointer



all:
	$(CXX) --std=c++17 -o $(bin) $(CXXFLAGS) $(SRC) $(INC) $(shell pkg-config --libs gl sfml-graphics)
