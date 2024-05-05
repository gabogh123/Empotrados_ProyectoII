/* module_id.c - automatically generated, do not edit */

#include <simics/build-id.h>
#include <simics/base/types.h>
#include <simics/util/help-macros.h>

#if defined(SIMICS_6_API)
#define BUILD_API "6"
#elif defined(SIMICS_5_API)
#define BUILD_API "5"
#elif defined(SIMICS_4_8_API)
#define BUILD_API "4.8"
#else
#define BUILD_API "?"
#endif

#define EXTRA "                                           "

EXPORTED const char _module_capabilities_[] =
	"VER:" SYMBOL_TO_STRING(SIM_VERSION_COMPAT) ";"
	"ABI:" SYMBOL_TO_STRING(SIM_VERSION) ";"
	"API:" BUILD_API ";"
	"BLD:" "0" ";"
	"BLD_NS:__simics_project__;"
	"BUILDDATE:" "1714623503" ";"
	"MOD:" "tomasulo" ";"
	"CLS:tomasulo;CLS:tomasulo_connection_t" ";"
	"HOSTTYPE:" "linux64" ";"
	"THREADSAFE;"
	EXTRA ";";
EXPORTED const char _module_date[] = "Thu May  2 00:18:23 2024";
EXPORTED void _simics_module_init(void);
extern void sim_iface_wrap_init(void);

void
_simics_module_init(void)
{

	init_local();
}
