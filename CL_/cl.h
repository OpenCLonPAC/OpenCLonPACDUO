#include <stdio.h>
#include "cl_platform.h"
#include "platform.h"
/******************************************************************************/

typedef struct _cl_platform_id *    cl_platform_id;
typedef struct _cl_device_id *      cl_device_id;
typedef struct _cl_context *        cl_context;
typedef struct _cl_command_queue *  cl_command_queue;
typedef struct _cl_mem *            cl_mem;
typedef struct _cl_program *        cl_program;
typedef struct _cl_kernel *         cl_kernel;
typedef struct _cl_event *          cl_event;
typedef struct _cl_sampler *        cl_sampler;

typedef cl_uint             cl_bool;                     /* WARNING!  Unlike cl_ types in cl_platform.h, cl_bool is not guaranteed to be the same size as the bool in kernels. */ 
typedef cl_ulong            cl_bitfield;
typedef cl_bitfield         cl_device_type;
typedef cl_uint             cl_platform_info;
typedef cl_uint             cl_device_info;
typedef cl_bitfield         cl_device_address_info;
typedef cl_bitfield         cl_device_fp_config;
typedef cl_uint             cl_device_mem_cache_type;
typedef cl_uint             cl_device_local_mem_type;
typedef cl_bitfield         cl_device_exec_capabilities;
typedef cl_bitfield         cl_command_queue_properties;

typedef intptr_t			cl_context_properties;
typedef cl_uint             cl_context_info;
typedef cl_uint             cl_command_queue_info;
typedef cl_uint             cl_channel_order;
typedef cl_uint             cl_channel_type;
typedef cl_bitfield         cl_mem_flags;
typedef cl_uint             cl_mem_object_type;
typedef cl_uint             cl_mem_info;
typedef cl_uint             cl_image_info;
typedef cl_uint             cl_addressing_mode;
typedef cl_uint             cl_filter_mode;
typedef cl_uint             cl_sampler_info;
typedef cl_bitfield         cl_map_flags;
typedef cl_uint             cl_program_info;
typedef cl_uint             cl_program_build_info;
typedef cl_int              cl_build_status;
typedef cl_uint             cl_kernel_info;
typedef cl_uint             cl_kernel_work_group_info;
typedef cl_uint             cl_event_info;
typedef cl_uint             cl_command_type;
typedef cl_uint             cl_profiling_info;

typedef struct _cl_image_format {
    cl_channel_order        image_channel_order;
    cl_channel_type         image_channel_data_type;
} cl_image_format;


/******************************************************************************/

// Macro names and corresponding values defined by OpenCL

#define CL_CHAR_BIT         8
#define CL_SCHAR_MAX        127
#define CL_SCHAR_MIN        (-127-1)
#define CL_CHAR_MAX         CL_SCHAR_MAX
#define CL_CHAR_MIN         CL_SCHAR_MIN
#define CL_UCHAR_MAX        255
#define CL_SHRT_MAX         32767
#define CL_SHRT_MIN         (-32767-1)
#define CL_USHRT_MAX        65535
#define CL_INT_MAX          2147483647
#define CL_INT_MIN          (-2147483647-1)
#define CL_UINT_MAX         0xffffffffU
#define CL_LONG_MAX         ((cl_long) 0x7FFFFFFFFFFFFFFFLL)
#define CL_LONG_MIN         ((cl_long) -0x7FFFFFFFFFFFFFFFLL - 1LL)
#define CL_ULONG_MAX        ((cl_ulong) 0xFFFFFFFFFFFFFFFFULL)

#define CL_FLT_DIG          6
#define CL_FLT_MANT_DIG     24
#define CL_FLT_MAX_10_EXP   +38
#define CL_FLT_MAX_EXP      +128
#define CL_FLT_MIN_10_EXP   -37
#define CL_FLT_MIN_EXP      -125
#define CL_FLT_RADIX        2
#define CL_FLT_MAX          0x1.fffffep127f
#define CL_FLT_MIN          0x1.0p-126f
#define CL_FLT_EPSILON      0x1.0p-23f

#define CL_DBL_DIG          15
#define CL_DBL_MANT_DIG     53
#define CL_DBL_MAX_10_EXP   +308
#define CL_DBL_MAX_EXP      +1024
#define CL_DBL_MIN_10_EXP   -307
#define CL_DBL_MIN_EXP      -1021
#define CL_DBL_RADIX        2
#define CL_DBL_MAX          0x1.fffffffffffffp1023
#define CL_DBL_MIN          0x1.0p-1022
#define CL_DBL_EPSILON      0x1.0p-52

/******************************************************************************/

// Error Codes
#define CL_SUCCESS                                  0
#define CL_DEVICE_NOT_FOUND                         -1
#define CL_DEVICE_NOT_AVAILABLE                     -2
#define CL_COMPILER_NOT_AVAILABLE                   -3
#define CL_DEVICE_COMPILER_NOT_AVAILABLE            -3
#define CL_MEM_OBJECT_ALLOCATION_FAILURE            -4
#define CL_OUT_OF_RESOURCES                         -5
#define CL_OUT_OF_HOST_MEMORY                       -6
#define CL_PROFILING_INFO_NOT_AVAILABLE             -7
#define CL_MEM_COPY_OVERLAP                         -8
#define CL_IMAGE_FORMAT_MISMATCH                    -9
#define CL_IMAGE_FORMAT_NOT_SUPPORTED               -10
#define CL_BUILD_PROGRAM_FAILURE                    -11
#define CL_MAP_FAILURE                              -12

#define CL_INVALID_VALUE                            -30
#define CL_INVALID_DEVICE_TYPE                      -31
#define CL_INVALID_PLATFORM                         -32
#define CL_INVALID_DEVICE                           -33
#define CL_INVALID_CONTEXT                          -34
#define CL_INVALID_QUEUE_PROPERTIES                 -35
#define CL_INVALID_COMMAND_QUEUE                    -36
#define CL_INVALID_HOST_PTR                         -37
#define CL_INVALID_MEM_OBJECT                       -38
#define CL_INVALID_IMAGE_FORMAT_DESCRIPTOR          -39
#define CL_INVALID_IMAGE_SIZE                       -40
#define CL_INVALID_SAMPLER                          -41
#define CL_INVALID_BINARY                           -42
#define CL_INVALID_BUILD_OPTIONS                    -43
#define CL_INVALID_PROGRAM                          -44
#define CL_INVALID_PROGRAM_EXECUTABLE               -45
#define CL_INVALID_KERNEL_NAME                      -46
#define CL_INVALID_KERNEL_DEFINITION                -47
#define CL_INVALID_KERNEL                           -48
#define CL_INVALID_ARG_INDEX                        -49
#define CL_INVALID_ARG_VALUE                        -50
#define CL_INVALID_ARG_SIZE                         -51
#define CL_INVALID_KERNEL_ARGS                      -52
#define CL_INVALID_WORK_DIMENSION                   -53
#define CL_INVALID_WORK_GROUP_SIZE                  -54
#define CL_INVALID_WORK_ITEM_SIZE                   -55
#define CL_INVALID_GLOBAL_OFFSET                    -56
#define CL_INVALID_EVENT_WAIT_LIST                  -57
#define CL_INVALID_EVENT                            -58
#define CL_INVALID_OPERATION                        -59
#define CL_INVALID_GL_OBJECT                        -60
#define CL_INVALID_BUFFER_SIZE                      -61
#define CL_INVALID_MIP_LEVEL                        -62

// OpenCL Version
#define CL_VERSION_1_0                              1

// cl_bool
#define CL_FALSE                                    0
#define CL_TRUE                                     1

// cl_platform_info
/*#define CL_PLATFORM_PROFILE                         0x0900
#define CL_PLATFORM_VERSION                         0x0901
#define CL_PLATFORM_NAME                            0x0902
#define CL_PLATFORM_VENDOR                          0x0903
#define CL_PLATFORM_EXTENSIONS                      0x0904
*/
// cl_device_type - bitfield
#define CL_DEVICE_TYPE_DEFAULT                      (1 << 0)
#define CL_DEVICE_TYPE_CPU                          (1 << 1)
#define CL_DEVICE_TYPE_GPU                          (1 << 2)
#define CL_DEVICE_TYPE_ACCELERATOR                  (1 << 3)
#define CL_DEVICE_TYPE_ALL                          0xFFFFFFFF

// cl_device_info
#define CL_DEVICE_TYPE                              0x1000
#define CL_DEVICE_VENDOR_ID                         0x1001
#define CL_DEVICE_MAX_COMPUTE_UNITS                 0x1002
#define CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS          0x1003
#define CL_DEVICE_MAX_WORK_GROUP_SIZE               0x1004
#define CL_DEVICE_MAX_WORK_ITEM_SIZES               0x1005
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR       0x1006
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT      0x1007
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT        0x1008
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG       0x1009
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT      0x100A
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE     0x100B
#define CL_DEVICE_MAX_CLOCK_FREQUENCY               0x100C
#define CL_DEVICE_ADDRESS_BITS                      0x100D
#define CL_DEVICE_MAX_READ_IMAGE_ARGS               0x100E
#define CL_DEVICE_MAX_WRITE_IMAGE_ARGS              0x100F
#define CL_DEVICE_MAX_MEM_ALLOC_SIZE                0x1010
#define CL_DEVICE_IMAGE2D_MAX_WIDTH                 0x1011
#define CL_DEVICE_IMAGE2D_MAX_HEIGHT                0x1012
#define CL_DEVICE_IMAGE3D_MAX_WIDTH                 0x1013
#define CL_DEVICE_IMAGE3D_MAX_HEIGHT                0x1014
#define CL_DEVICE_IMAGE3D_MAX_DEPTH                 0x1015
#define CL_DEVICE_IMAGE_SUPPORT                     0x1016
#define CL_DEVICE_MAX_PARAMETER_SIZE                0x1017
#define CL_DEVICE_MAX_SAMPLERS                      0x1018
#define CL_DEVICE_MEM_BASE_ADDR_ALIGN               0x1019
#define CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE          0x101A
#define CL_DEVICE_SINGLE_FP_CONFIG                  0x101B
#define CL_DEVICE_GLOBAL_MEM_CACHE_TYPE             0x101C
#define CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE         0x101D
#define CL_DEVICE_GLOBAL_MEM_CACHE_SIZE             0x101E
#define CL_DEVICE_GLOBAL_MEM_SIZE                   0x101F
#define CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE          0x1020
#define CL_DEVICE_MAX_CONSTANT_ARGS                 0x1021
#define CL_DEVICE_LOCAL_MEM_TYPE                    0x1022
#define CL_DEVICE_LOCAL_MEM_SIZE                    0x1023
#define CL_DEVICE_ERROR_CORRECTION_SUPPORT          0x1024
#define CL_DEVICE_PROFILING_TIMER_RESOLUTION        0x1025
#define CL_DEVICE_ENDIAN_LITTLE                     0x1026
#define CL_DEVICE_AVAILABLE                         0x1027
#define CL_DEVICE_COMPILER_AVAILABLE                0x1028
#define CL_DEVICE_EXECUTION_CAPABILITIES            0x1029
#define CL_DEVICE_QUEUE_PROPERTIES                  0x102A
#define CL_DEVICE_NAME                              0x102B
#define CL_DEVICE_VENDOR                            0x102C
#define CL_DRIVER_VERSION                           0x102D
#define CL_DEVICE_PROFILE                           0x102E
#define CL_DEVICE_VERSION                           0x102F
#define CL_DEVICE_EXTENSIONS                        0x1030
#define CL_DEVICE_PLATFORM                          0x1031
	
// cl_device_fp_config - bitfield
#define CL_FP_DENORM                                (1 << 0)
#define CL_FP_INF_NAN                               (1 << 1)
#define CL_FP_ROUND_TO_NEAREST                      (1 << 2)
#define CL_FP_ROUND_TO_ZERO                         (1 << 3)
#define CL_FP_ROUND_TO_INF                          (1 << 4)
#define CL_FP_FMA                                   (1 << 5)

// cl_device_mem_cache_type
#define CL_NONE                                     0x0
#define CL_READ_ONLY_CACHE                          0x1
#define CL_READ_WRITE_CACHE                         0x2

// cl_device_local_mem_type
#define CL_LOCAL                                    0x1
#define CL_GLOBAL                                   0x2

// cl_device_exec_capabilities - bitfield
#define CL_EXEC_KERNEL                              (1 << 0)
#define CL_EXEC_NATIVE_KERNEL                       (1 << 1)

// cl_command_queue_properties - bitfield
#define CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE      (1 << 0)
#define CL_QUEUE_PROFILING_ENABLE                   (1 << 1)

// cl_context_info
#define CL_CONTEXT_REFERENCE_COUNT                  0x1080
#define CL_CONTEXT_DEVICES                          0x1081
#define CL_CONTEXT_PROPERTIES                       0x1082

// cl_context_properties
#define CL_CONTEXT_PLATFORM                         0x1084

// cl_command_queue_info
#define CL_QUEUE_CONTEXT                            0x1090
#define CL_QUEUE_DEVICE                             0x1091
#define CL_QUEUE_REFERENCE_COUNT                    0x1092
#define CL_QUEUE_PROPERTIES                         0x1093

// cl_mem_flags - bitfield
#define CL_MEM_READ_WRITE                           (1 << 0)
#define CL_MEM_WRITE_ONLY                           (1 << 1)
#define CL_MEM_READ_ONLY                            (1 << 2)
#define CL_MEM_USE_HOST_PTR                         (1 << 3)
#define CL_MEM_ALLOC_HOST_PTR                       (1 << 4)
#define CL_MEM_COPY_HOST_PTR                        (1 << 5)

// cl_channel_order
#define CL_R                                        0x10B0
#define CL_A                                        0x10B1
#define CL_RG                                       0x10B2
#define CL_RA                                       0x10B3
#define CL_RGB                                      0x10B4
#define CL_RGBA                                     0x10B5
#define CL_BGRA                                     0x10B6
#define CL_ARGB                                     0x10B7
#define CL_INTENSITY                                0x10B8
#define CL_LUMINANCE                                0x10B9

// cl_channel_type
#define CL_SNORM_INT8                               0x10D0
#define CL_SNORM_INT16                              0x10D1
#define CL_UNORM_INT8                               0x10D2
#define CL_UNORM_INT16                              0x10D3
#define CL_UNORM_SHORT_565                          0x10D4
#define CL_UNORM_SHORT_555                          0x10D5
#define CL_UNORM_INT_101010                         0x10D6
#define CL_SIGNED_INT8                              0x10D7
#define CL_SIGNED_INT16                             0x10D8
#define CL_SIGNED_INT32                             0x10D9
#define CL_UNSIGNED_INT8                            0x10DA
#define CL_UNSIGNED_INT16                           0x10DB
#define CL_UNSIGNED_INT32                           0x10DC
#define CL_HALF_FLOAT                               0x10DD
#define CL_FLOAT                                    0x10DE

// cl_mem_object_type
#define CL_MEM_OBJECT_BUFFER                        0x10F0
#define CL_MEM_OBJECT_IMAGE2D                       0x10F1
#define CL_MEM_OBJECT_IMAGE3D                       0x10F2

// cl_mem_info
#define CL_MEM_TYPE                                 0x1100
#define CL_MEM_FLAGS                                0x1101
#define CL_MEM_SIZE                                 0x1102
#define CL_MEM_HOST_PTR                             0x1103
#define CL_MEM_MAP_COUNT                            0x1104
#define CL_MEM_REFERENCE_COUNT                      0x1105
#define CL_MEM_CONTEXT                              0x1106

// cl_image_info
#define CL_IMAGE_FORMAT                             0x1110
#define CL_IMAGE_ELEMENT_SIZE                       0x1111
#define CL_IMAGE_ROW_PITCH                          0x1112
#define CL_IMAGE_SLICE_PITCH                        0x1113
#define CL_IMAGE_WIDTH                              0x1114
#define CL_IMAGE_HEIGHT                             0x1115
#define CL_IMAGE_DEPTH                              0x1116

// cl_addressing_mode
#define CL_ADDRESS_NONE                             0x1130
#define CL_ADDRESS_CLAMP_TO_EDGE                    0x1131
#define CL_ADDRESS_CLAMP                            0x1132
#define CL_ADDRESS_REPEAT                           0x1133

// cl_filter_mode
#define CL_FILTER_NEAREST                           0x1140
#define CL_FILTER_LINEAR                            0x1141

// cl_sampler_info
#define CL_SAMPLER_REFERENCE_COUNT                  0x1150
#define CL_SAMPLER_CONTEXT                          0x1151
#define CL_SAMPLER_NORMALIZED_COORDS                0x1152
#define CL_SAMPLER_ADDRESSING_MODE                  0x1153
#define CL_SAMPLER_FILTER_MODE                      0x1154

// cl_map_flags - bitfield
#define CL_MAP_READ                                 (1 << 0)
#define CL_MAP_WRITE                                (1 << 1)

// cl_program_info
#define CL_PROGRAM_REFERENCE_COUNT                  0x1160
#define CL_PROGRAM_CONTEXT                          0x1161
#define CL_PROGRAM_NUM_DEVICES                      0x1162
#define CL_PROGRAM_DEVICES                          0x1163
#define CL_PROGRAM_SOURCE                           0x1164
#define CL_PROGRAM_BINARY_SIZES                     0x1165
#define CL_PROGRAM_BINARIES                         0x1166

// cl_program_build_info
#define CL_PROGRAM_BUILD_STATUS                     0x1181
#define CL_PROGRAM_BUILD_OPTIONS                    0x1182
#define CL_PROGRAM_BUILD_LOG                        0x1183

// cl_build_status
#define CL_BUILD_SUCCESS                            0
#define CL_BUILD_NONE                               -1
#define CL_BUILD_ERROR                              -2
#define CL_BUILD_IN_PROGRESS                        -3

// cl_kernel_info
#define CL_KERNEL_FUNCTION_NAME                     0x1190
#define CL_KERNEL_NUM_ARGS                          0x1191
#define CL_KERNEL_REFERENCE_COUNT                   0x1192
#define CL_KERNEL_CONTEXT                           0x1193
#define CL_KERNEL_PROGRAM                           0x1194

// cl_kernel_work_group_info
#define CL_KERNEL_WORK_GROUP_SIZE                   0x11B0
#define CL_KERNEL_COMPILE_WORK_GROUP_SIZE           0x11B1
#define CL_KERNEL_LOCAL_MEM_SIZE                    0x11B2

// cl_event_info
#define CL_EVENT_COMMAND_QUEUE                      0x11D0
#define CL_EVENT_COMMAND_TYPE                       0x11D1
#define CL_EVENT_REFERENCE_COUNT                    0x11D2
#define CL_EVENT_COMMAND_EXECUTION_STATUS           0x11D3

// cl_command_type
#define CL_COMMAND_NDRANGE_KERNEL                   0x11F0
#define CL_COMMAND_TASK                             0x11F1
#define CL_COMMAND_NATIVE_KERNEL                    0x11F2
#define CL_COMMAND_READ_BUFFER                      0x11F3
#define CL_COMMAND_WRITE_BUFFER                     0x11F4
#define CL_COMMAND_COPY_BUFFER                      0x11F5
#define CL_COMMAND_READ_IMAGE                       0x11F6
#define CL_COMMAND_WRITE_IMAGE                      0x11F7
#define CL_COMMAND_COPY_IMAGE                       0x11F8
#define CL_COMMAND_COPY_IMAGE_TO_BUFFER             0x11F9
#define CL_COMMAND_COPY_BUFFER_TO_IMAGE             0x11FA
#define CL_COMMAND_MAP_BUFFER                       0x11FB
#define CL_COMMAND_MAP_IMAGE                        0x11FC
#define CL_COMMAND_UNMAP_MEM_OBJECT                 0x11FD
#define CL_COMMAND_MARKER                           0x11FE
#define CL_COMMAND_ACQUIRE_GL_OBJECTS               0x11FF
#define CL_COMMAND_RELEASE_GL_OBJECTS               0x1200
#define CL_COMMAND_WAIT_FOR_EVENTS                  0x1201 //TODO:DELETE ME
#define CL_COMMAND_BARRIER                          0x1202 //TODO:DELETE ME

// command execution status
#define CL_COMPLETE                                 0x0
#define CL_RUNNING                                  0x1
#define CL_SUBMITTED                                0x2
#define CL_QUEUED                                   0x3
  
// cl_profiling_info
#define CL_PROFILING_COMMAND_QUEUED                 0x1280
#define CL_PROFILING_COMMAND_SUBMIT                 0x1281
#define CL_PROFILING_COMMAND_START                  0x1282
#define CL_PROFILING_COMMAND_END                    0x1283

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

/*	if ( NULL == g_hPlatform )
	{
		_create_platform();
	}
*/
	if (num_platforms) *num_platforms = 1;

	if (platforms == NULL) return CL_SUCCESS;

//	platforms[0] = g_hPlatform;

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
/*	int i		= 0;
	int retIdx	= 0;
	cl_device_type	match_dev_type;
	cl_rtl_device	pDevice;

	if (device_type != CL_DEVICE_TYPE_ALL && 
		(!(device_type & (CL_DEVICE_TYPE_DEFAULT | CL_DEVICE_TYPE_CPU | CL_DEVICE_TYPE_GPU | CL_DEVICE_TYPE_ACCELERATOR))))
	{
		return CL_INVALID_DEVICE_TYPE;
	}

	if ((num_entries == 0 && devices != NULL) ||
		(num_devices == NULL && devices == NULL))
	{
		return CL_INVALID_VALUE;
	}

	if(FALSE == _devapi_init_device)
	{
		devapi_init_dev();#include "cl_platform.h"
	}

	while (NULL != g_list_device_id[i].pobj)
	{
		pDevice = hdlapi_get_obj(cl_rtl_device, &g_list_device_id[i]);
		match_dev_type = pDevice->pDrv->di->qi.dev_type & device_type;

		CL_DBG_MSG("cur_idx [%x]\n", i);
		CL_DBG_MSG("g_list_device_id [%x]\n", &g_list_device_id[i]);
		CL_DBG_MSG("dev_name : %s\n", pDevice->pDrv->di->qi.dev_name);
		CL_DBG_MSG("dev_type : %x\n", (cl_int)pDevice->pDrv->di->qi.dev_type);
		CL_DBG_MSG("dev_cu   : %d\n", pDevice->pDrv->di->qi.max_compute_unit);
		CL_DBG_MSG("req_type : %x\n", (cl_int)(device_type));
		CL_DBG_MSG("----------------------------\n", device_type);
		CL_DBG_MSG("matched_type : %x\n", (cl_int)match_dev_type);
		
		if ( match_dev_type )
		{
			if(NULL != devices)
			{
				devices[retIdx] = &g_list_device_id[i];
			}

			_start_scheduler(pDevice);

			retIdx++;
		}

		i++;
	}

	if ( NULL != num_devices)
	{
		*num_devices = retIdx;
	}

	if ( 0 == retIdx )
	{
		return CL_DEVICE_NOT_FOUND;
	}

	CL_DBG_MSG("clGetDeviceIDs success!\n", DBG_END_MSG);
*/
	return CL_SUCCESS;
}


cl_int
clGetDeviceInfo(	cl_device_id	device,
					cl_device_info	param_name,
					size_t			param_value_size,
					void*			param_value,
					size_t*			param_value_size_ret)
{
/*	pstDEVICE_INFO	pDevInfo;

	//if device is not valid.
	if(NULL == device)
	{
		return CL_INVALID_DEVICE;
	}

	if(NULL == device->pobj)
	{
		return CL_INVALID_DEVICE;
	}

	if(FALSE == _devapi_init_device)
	{
		return CL_INVALID_DEVICE;
	}

	pDevInfo = hdlapi_get_obj(cl_rtl_device, device)->pDrv->di;
*/
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

