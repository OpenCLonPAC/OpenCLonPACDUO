#include <string.h>
#include <memory.h>
//#include "common.h"
#define	STR_PLATFORM_PROFILE	"FULL_PROFILE"
#define	STR_PLATFORM_VERSION	"OpenCL 1.0 rev43"
#define	STR_PLATFORM_NAME		"CL_PLATFORM_SEC"
#define	STR_PLATFORM_VENDOR		"SNU-SAMSUNG"
#define	STR_PLATFORM_EXTENSIONS	""
//#define	CL_PLATFORM_ID_SEC		(0x000002EAU)

static char platform_profile[] = STR_PLATFORM_PROFILE;
static char platform_version[] = STR_PLATFORM_VERSION;
static char platform_name[]    = STR_PLATFORM_NAME;
static char platform_vendor[]  = STR_PLATFORM_VENDOR;
static char platform_extensions[] = STR_PLATFORM_EXTENSIONS;


//////////////////////////////////////////////////////////////
// Variable
//////////////////////////////////////////////////////////////
//unsigned int unique_id;

//static cl_platform_id g_hPlatform = NULL; 
//static cl_rtl_platform g_pPlatform = {0};

//////////////////////////////////////////////////////////////
// STATIC FUNCTIONS
//////////////////////////////////////////////////////////////
static void
_create_platform()
{
//	hdlapi_create(g_hPlatform, cl_platform_id);
//	cmnapi_create_rtl_obj(g_pPlatform, cl_rtl_platform);
//	hdlapi_map_obj(g_hPlatform, g_pPlatform);
//	g_pPlatform->id  = CL_PLATFORM_ID_SEC;
}


static void
_destroy_platform()
{
//	hdlapi_unmap_obj(g_hPlatform, g_pPlatform);
//	cmnapi_destroy(g_pPlatform);
//	hdlapi_destroy(g_hPlatform);
}

