/**
 * \file
 * \brief Dear Im Gui inclusion wrapper.
 * \note Used to disable some specific compiler flags
 */

#ifndef IMGUI_HH_
# define IMGUI_HH_

// TODO other compilers support
# pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#   pragma GCC diagnostic ignored "-Wunused-variable"
#   pragma GCC diagnostic ignored "-Wlong-long"
#   pragma GCC diagnostic ignored "-Wconversion"
#   pragma GCC diagnostic ignored "-Wold-style-cast"

#   include <imgui.h>
#   include <imgui-SFML.h>
# pragma GCC diagnostic pop


#endif /* !IMGUI_HH_ */
