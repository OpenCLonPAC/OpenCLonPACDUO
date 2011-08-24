#include <stdio.h>
#include <stdint.h>
#define cmnapi_getinfo_array(param,type,value,length)	        \
case param:					                \
{							        \
	size_t size = sizeof(type) * length;		        \
	if (param_value)				        \
	{						        \
		if (param_value_size < size)		        \
			return CL_INVALID_VALUE;	        \
		memcpy(param_value, value, size);	        \
	}						        \
	if (param_value_size_ret) *param_value_size_ret = size;	\
	break;						        \
}
#define cmnapi_getinfo(param,type,value)                        \
case param:                                                     \
{                                                               \
        size_t size = sizeof(type);                             \
        if (param_value)                                        \
        {                                                       \
                if (param_value_size < size)                    \
                        return CL_INVALID_VALUE;                \
                memcpy(param_value, &value, size);              \
        }                                                       \
        if (param_value_size_ret) *param_value_size_ret = size; \
        break;                                                  \
}
#define cmnapi_getinfo_default() default: return CL_INVALID_VALUE;
/*
#define hdlapi_create( ptr_name, ptr_type)                  \
(ptr_name) = (ptr_type) malloc(sizeof(struct _##ptr_type)); \
halapi_atomic_set(&((ptr_name)->ref), 1)
#define HOST_ATOMIC_T           host_atomic_t*/
#define	STR_PLATFORM_PROFILE	"PACDUO_PROFILE"//"FULL_PROFILE" "EMBEDDED_PROFILE"
#define	STR_PLATFORM_VERSION	"OpenCL 0.0"
#define	STR_PLATFORM_NAME	"PACDUO"
#define	STR_PLATFORM_VENDOR	"ITRI"
#define	STR_PLATFORM_EXTENSIONS	""

/* scalar types  */
typedef int8_t          cl_char;
typedef uint8_t         cl_uchar;
typedef int16_t         cl_short    __attribute__((aligned(2)));
typedef uint16_t        cl_ushort   __attribute__((aligned(2)));
typedef int32_t         cl_int      __attribute__((aligned(4)));
typedef uint32_t        cl_uint     __attribute__((aligned(4)));
typedef int64_t         cl_long     __attribute__((aligned(8)));
typedef uint64_t        cl_ulong    __attribute__((aligned(8)));

typedef uint16_t        cl_half     __attribute__((aligned(2)));
typedef float           cl_float    __attribute__((aligned(4)));
typedef double          cl_double   __attribute__((aligned(8)));


typedef cl_uint		    cl_platform_id;
typedef cl_uint  	    cl_device_id;
typedef cl_uint             cl_platform_info;
typedef cl_uint             cl_device_info;
typedef cl_ulong            cl_bitfield;
typedef cl_bitfield         cl_device_type;

static char platform_profile[] = STR_PLATFORM_PROFILE;
static char platform_version[] = STR_PLATFORM_VERSION;
static char platform_name[]    = STR_PLATFORM_NAME;
static char platform_vendor[]  = STR_PLATFORM_VENDOR;
static char platform_extensions[] = STR_PLATFORM_EXTENSIONS;

typedef struct _cl_rtl_context 
{
//        HOST_ATOMIC_T                   ref;
//        cl_handle                       pHandle;
//        cl_context_properties*  properties;
        unsigned int                    num_devices;
        cl_device_id*                   phDevices;
//        logging_fn                      pfn_notify;
        void*                           user_data;
} cl_st_rtl_context, *cl_rtl_context;



typedef struct _cl_context *        cl_context;

// cl_platform_info
#define CL_PLATFORM_PROFILE                         0x0900
#define CL_PLATFORM_VERSION                         0x0901
#define CL_PLATFORM_NAME                            0x0902
#define CL_PLATFORM_VENDOR                          0x0903
#define CL_PLATFORM_EXTENSIONS                      0x0904

// cl_device_type - bitfield
#define CL_DEVICE_TYPE_DEFAULT                      (1 << 0)
#define CL_DEVICE_TYPE_CPU                          (1 << 1)
#define CL_DEVICE_TYPE_GPU                          (1 << 2)
#define CL_DEVICE_TYPE_ACCELERATOR                  (1 << 3)
#define CL_DEVICE_TYPE_ALL                          0xFFFFFFFF

// Error Codes
#define CL_SUCCESS                                  0
#define CL_INVALID_VALUE                          -30
#define CL_INVALID_DEVICE_TYPE                    -31
#define CL_INVALID_DEVICE                         -33

/********************************************************************************************************/

//////////////////////////////////////////////////////////////
// OPENCL PLATFORM API
//////////////////////////////////////////////////////////////
cl_int
clGetPlatformIDs(cl_uint          num_entries,
                 cl_platform_id * platforms,
                 cl_uint *        num_platforms)
{
	if ((num_entries == 0 && platforms != NULL) || (num_platforms == NULL && platforms == NULL))
	{
		return CL_INVALID_VALUE;
	}

	if (num_platforms) *num_platforms = 1;

	if (platforms == NULL) return CL_SUCCESS;

	platforms[0] = 1;

	return CL_SUCCESS;
}

cl_int
clGetPlatformInfo(cl_platform_id   platform, 
                  cl_platform_info param_name,
                  size_t           param_value_size, 
                  void *           param_value,
                  size_t *         param_value_size_ret)
{
	switch(param_name)
	{
		cmnapi_getinfo_array(CL_PLATFORM_PROFILE, char, platform_profile, strlen(platform_profile) + 1);
		cmnapi_getinfo_array(CL_PLATFORM_VERSION, char, platform_version, strlen(platform_version) + 1);
		cmnapi_getinfo_array(CL_PLATFORM_NAME, char, platform_name, strlen(platform_name) + 1);
		cmnapi_getinfo_array(CL_PLATFORM_VENDOR, char, platform_vendor, strlen(platform_vendor) + 1);
		cmnapi_getinfo_array(CL_PLATFORM_EXTENSIONS, char, platform_extensions, strlen(platform_extensions) + 1);
		cmnapi_getinfo_default();
	}

	return CL_SUCCESS;
}

//////////////////////////////////////////////////////////////
// OPENCL DEVICE API
//////////////////////////////////////////////////////////////
cl_int
clGetDeviceIDs(cl_platform_id   platform,
               cl_device_type   device_type, 
               cl_uint          num_entries, 
               cl_device_id *   devices, 
               cl_uint *        num_devices)
{
	int i		= 0;
	int retIdx	= 0;
	cl_device_type	match_dev_type;

	if (device_type != (CL_DEVICE_TYPE_ALL || CL_DEVICE_TYPE_ACCELERATOR))
	{
		return CL_INVALID_DEVICE_TYPE;
	}

	if ((num_entries == 0 && devices != NULL) || (num_devices == NULL && devices == NULL))
	{
		return CL_INVALID_VALUE;
	}

	if(NULL != devices)
	{
		devices[0] = 1;
	}
		
	if ( NULL != num_devices)
	{
		*num_devices = 1;
	}
	return CL_SUCCESS;
}


cl_int
clGetDeviceInfo(	cl_device_id	device,
			cl_device_info	param_name,
			size_t			param_value_size,
			void*			param_value,
			size_t*			param_value_size_ret)
{
	//if device is not valid.
	if(NULL == device)
	{
		return CL_INVALID_DEVICE;
	}

	switch(param_name)
	{
/*		cmnapi_getinfo(CL_DEVICE_TYPE, cl_device_type, pDevInfo->qi.dev_type);
		cmnapi_getinfo(CL_DEVICE_VENDOR_ID, cl_uint, pDevInfo->qi.dev_vendor_id);
		cmnapi_getinfo(CL_DEVICE_MAX_COMPUTE_UNITS, cl_uint, pDevInfo->qi.max_compute_unit);
		cmnapi_getinfo(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, cl_uint, pDevInfo->qi.max_workitem_dims);
		cmnapi_getinfo_array(CL_DEVICE_MAX_WORK_ITEM_SIZES, size_t, pDevInfo->qi.max_workitem_size, pDevInfo->qi.max_workitem_dims);
		cmnapi_getinfo(CL_DEVICE_MAX_WORK_GROUP_SIZE, size_t, pDevInfo->qi.max_workgroup_size);
		cmnapi_getinfo(CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, cl_uint, pDevInfo->qi.preferred_vec_width_char);
		cmnapi_getinfo(CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, cl_uint, pDevInfo->qi.preferred_vec_width_short);
		cmnapi_getinfo(CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, cl_uint, pDevInfo->qi.preferred_vec_width_int);
		cmnapi_getinfo(CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, cl_uint, pDevInfo->qi.preferred_vec_width_long);
		cmnapi_getinfo(CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, cl_uint, pDevInfo->qi.preferred_vec_width_float);
		cmnapi_getinfo(CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, cl_uint, pDevInfo->qi.preferred_vec_width_double);
		cmnapi_getinfo(CL_DEVICE_MAX_CLOCK_FREQUENCY, cl_uint, pDevInfo->qi.max_clock_freq);
		cmnapi_getinfo(CL_DEVICE_ADDRESS_BITS, cl_uint, pDevInfo->qi.dev_addr_bits);
		cmnapi_getinfo(CL_DEVICE_MAX_MEM_ALLOC_SIZE, cl_ulong, pDevInfo->qi.max_mem_alloc_size);

		cmnapi_getinfo(CL_DEVICE_IMAGE_SUPPORT, cl_bool, pDevInfo->qi.dev_img_support);
		cmnapi_getinfo(CL_DEVICE_MAX_READ_IMAGE_ARGS, cl_uint, pDevInfo->qi.dev_max_read_img_args);
		cmnapi_getinfo(CL_DEVICE_MAX_WRITE_IMAGE_ARGS, cl_uint, pDevInfo->qi.dev_max_write_img_args);
		cmnapi_getinfo(CL_DEVICE_IMAGE2D_MAX_WIDTH, size_t, pDevInfo->qi.dev_img2d_max_width);
		cmnapi_getinfo(CL_DEVICE_IMAGE2D_MAX_HEIGHT, size_t, pDevInfo->qi.dev_img2d_max_height);
		cmnapi_getinfo(CL_DEVICE_IMAGE3D_MAX_WIDTH, size_t, pDevInfo->qi.dev_img3d_max_width);
		cmnapi_getinfo(CL_DEVICE_IMAGE3D_MAX_HEIGHT, size_t, pDevInfo->qi.dev_img3d_max_height);
		cmnapi_getinfo(CL_DEVICE_IMAGE3D_MAX_DEPTH, size_t, pDevInfo->qi.dev_img3d_max_depth);
		cmnapi_getinfo(CL_DEVICE_MAX_SAMPLERS, cl_uint, pDevInfo->qi.dev_max_samplers);

		cmnapi_getinfo(CL_DEVICE_MAX_PARAMETER_SIZE, size_t, pDevInfo->qi.max_param_size);

		cmnapi_getinfo(CL_DEVICE_MEM_BASE_ADDR_ALIGN, cl_uint, pDevInfo->qi.dev_mem_base_addr_align);
		cmnapi_getinfo(CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE, cl_uint, pDevInfo->qi.dev_min_data_type_align_size);

		cmnapi_getinfo(CL_DEVICE_SINGLE_FP_CONFIG, cl_device_fp_config, pDevInfo->qi.dev_single_fp_conf);

		cmnapi_getinfo(CL_DEVICE_GLOBAL_MEM_CACHE_TYPE, cl_device_mem_cache_type, pDevInfo->qi.dev_global_cache_type);
		cmnapi_getinfo(CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, cl_uint, pDevInfo->qi.dev_global_cacheline_size);
		cmnapi_getinfo(CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, cl_ulong, pDevInfo->qi.dev_global_cache_size);
		cmnapi_getinfo(CL_DEVICE_GLOBAL_MEM_SIZE, cl_ulong, pDevInfo->qi.dev_global_mem_size);

		cmnapi_getinfo(CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, cl_ulong, pDevInfo->qi.max_const_buf_size);
		cmnapi_getinfo(CL_DEVICE_MAX_CONSTANT_ARGS, cl_uint, pDevInfo->qi.max_const_args);

		cmnapi_getinfo(CL_DEVICE_LOCAL_MEM_TYPE, cl_device_local_mem_type, pDevInfo->qi.dev_local_mem_type);
		cmnapi_getinfo(CL_DEVICE_LOCAL_MEM_SIZE, cl_ulong, pDevInfo->qi.dev_local_mem_size);
		cmnapi_getinfo(CL_DEVICE_ERROR_CORRECTION_SUPPORT, cl_bool, pDevInfo->qi.dev_err_correct_support);

		cmnapi_getinfo(CL_DEVICE_PROFILING_TIMER_RESOLUTION, size_t, pDevInfo->qi.dev_profiling_timer_res);
		
		cmnapi_getinfo(CL_DEVICE_ENDIAN_LITTLE, cl_bool, pDevInfo->qi.dev_endian_little);
		cmnapi_getinfo(CL_DEVICE_AVAILABLE, cl_bool, pDevInfo->qi.dev_available);
		cmnapi_getinfo(CL_DEVICE_COMPILER_AVAILABLE, cl_bool, pDevInfo->qi.dev_compiler_available);

		cmnapi_getinfo(CL_DEVICE_EXECUTION_CAPABILITIES, cl_device_exec_capabilities, pDevInfo->qi.dev_execution_capabilities);
		cmnapi_getinfo(CL_DEVICE_QUEUE_PROPERTIES, cl_command_queue_properties, pDevInfo->qi.dev_queue_prop);

		cmnapi_getinfo(CL_DEVICE_PLATFORM, cl_platform_id, pDevInfo->qi.dev_platform);

		cmnapi_getinfo_array(CL_DEVICE_NAME, char, pDevInfo->qi.dev_name, strlen(pDevInfo->qi.dev_name) + 1);
		cmnapi_getinfo_array(CL_DEVICE_VENDOR, char, pDevInfo->qi.dev_vendor, strlen(pDevInfo->qi.dev_vendor) + 1);
		cmnapi_getinfo_array(CL_DRIVER_VERSION, char, pDevInfo->qi.drv_version, strlen(pDevInfo->qi.drv_version) + 1);
		cmnapi_getinfo_array(CL_DEVICE_PROFILE, char, pDevInfo->qi.dev_profile, strlen(pDevInfo->qi.dev_profile) + 1);
		cmnapi_getinfo_array(CL_DEVICE_VERSION, char, pDevInfo->qi.dev_version, strlen(pDevInfo->qi.dev_version) + 1);
		cmnapi_getinfo_array(CL_DEVICE_EXTENSIONS, char, pDevInfo->qi.dev_extensions, strlen(pDevInfo->qi.dev_extensions) + 1);

		cmnapi_getinfo_default();
*/	}

	return CL_SUCCESS;
}

//////////////////////////////////////////////////////////////
// OPENCL CONTEXT API
//////////////////////////////////////////////////////////////
/*
cl_context
clCreateContext(cl_context_properties*		properties,
                cl_uint				num_devices,
                const cl_device_id*		phDevices,
		logging_fn			pfn_notify,
                void*				user_data,
                cl_int*				errcode_ret)
{
	cl_int ret = CL_SUCCESS;
	cl_context hContext;
	cl_rtl_context pContext;

	if (phDevices == NULL)	ret = CL_INVALID_VALUE;
	if (num_devices == 0)	ret = CL_INVALID_VALUE;
	if (pfn_notify == NULL && user_data != NULL) ret = CL_INVALID_VALUE;
//	if (devapi_contains_invalid_dev((cl_device_id*) phDevices, num_devices)) ret = CL_INVALID_DEVICE;

	if (ret != CL_SUCCESS)
	{
		goto outdoor;
	}

	hdlapi_create(hContext, cl_context);
//	cmnapi_create_rtl_obj(pContext, cl_rtl_context);
//	hdlapi_map_obj( hContext, pContext);

	pContext->properties	= properties;
	pContext->num_devices	= num_devices;
	pContext->pfn_notify	= pfn_notify;
	pContext->user_data	= user_data;
	pContext->phDevices	= (cl_device_id*)malloc(num_devices * sizeof(cl_device_id));

//	CL_DBG_ASSERT(pContext->phDevices);

	memcpy( pContext->phDevices, phDevices, num_devices * sizeof(cl_device_id));

outdoor:
	if(NULL != errcode_ret)
	{
		*errcode_ret = ret;
	}

	return hContext;
}
*/

