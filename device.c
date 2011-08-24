#include <internal.h>
#include <string.h>
#include <memory.h>
#include <stdio.h>
#include <sched.h>

//__CL_DEFINE_MODULE_NAME__("HOST_DEVICE");

//////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
//////////////////////////////////////////////////////////////
cl_device_id			g_list_device_id;

static cl_rtl_device	g_list_rtl_device;
static int				_rtl_added_device_count = 0;
static int				_devapi_init_device = FALSE;

//////////////////////////////////////////////////////////////
// MACRO FUNCTION
//////////////////////////////////////////////////////////////

#define SET_NULL_DEVICE_ID(pdev_id)	(pdev_id)->pobj = NULL

//////////////////////////////////////////////////////////////
// STATIC FUNCTION
//////////////////////////////////////////////////////////////
static void
_runtime_thread_affinity()
{
#if defined(RUNTIME_CORE_ID)
	unsigned long mask = RUNTIME_CORE_ID; /* processor 0 */  
	/* bind process to processor 0 */  
	if (sched_setaffinity(0, sizeof(mask), /*(cpu_set_t*)*/&mask) <0) 
	{   
		CL_DBG_ERR("Failed to runtime sched_setaffinity\n", DBG_END_MSG);
	}   
	else
	{
		CL_DBG_MSG("Set runtime sched_setaffinity : Core ID %d\n", RUNTIME_CORE_ID);
		printf("Set runtime sched_setaffinity : Core ID %d\n", RUNTIME_CORE_ID);
	}
#endif
}


static cl_int
_init_device_list(	IN pstDEVICE_DRIVER* host_driver_list, 
					OUT cl_rtl_device* plist_rtl_device, 
					OUT cl_device_id* plist_device_id)
{
	int device_count = 0;

	while(NULL != host_driver_list[device_count])
	{
		device_count++;
	}

	if(device_count != 0)
	{
		//allocate device object.
		*plist_rtl_device = (cl_rtl_device)malloc((device_count) * sizeof(struct _cl_rtl_device));

		//allocate device id include null device.
		*plist_device_id = (struct _cl_device_id*)malloc((device_count+1) * sizeof(struct _cl_device_id));

		CL_DBG_ASSERT(*plist_device_id);
		
		return CL_SUCCESS;
	}

	return CL_ERROR;
}

static cl_int
_add_device(pstDEVICE_DRIVER	pDrv)
{
	cl_rtl_device	pDevice;
	cl_device_id	pDevID;

	if(NULL == pDrv)
	{
		return CL_ERROR;
	}

	//Device info update.
	pDrv->op->init();

	if(CL_FALSE == pDrv->di->qi.dev_available)
	{
		pDrv->op->uninit();
		return CL_ERROR;
	}

	pDevID = &g_list_device_id[_rtl_added_device_count];
	pDevice	= &g_list_rtl_device[_rtl_added_device_count];

	hdlapi_map_obj(pDevID, pDevice);
	
	//Device object initialization.
	pDevice->pHandle = (cl_handle)pDevID;
	pDevice->id		= _rtl_added_device_count;
	pDevice->pDrv	= pDrv;
	pDevice->pJQ	= jobapi_create_jobqueue(pDevice);
	pDevice->pKE	= exeapi_create_kernel_executor(pDevice);
	pDevice->pME	= exeapi_create_memory_executor(pDevice);
	pDevice->pScheduler	= schapi_create_scheduler(pDevice);
	pDevice->bTerminated = FALSE;
	pDevice->bSchedulerStarted = CL_FALSE;

	_rtl_added_device_count++;

	//set next device id to null.
	SET_NULL_DEVICE_ID(&g_list_device_id[_rtl_added_device_count]);

	return CL_SUCCESS;
}

static cl_int
_remove_device_all(void)
{
	cl_device_id	pDevID;
	cl_rtl_device	pDevice;
	
	while(_rtl_added_device_count--)
	{
		pDevID = &g_list_device_id[_rtl_added_device_count];
		pDevice	= &g_list_rtl_device[_rtl_added_device_count];

		hdlapi_unmap_obj(pDevID, pDevice);

		jobapi_destroy_jobqueue(pDevice->pJQ);

		CL_DBG_MSG("jobapi_destroy_jobqueue\n", DBG_END_MSG);

		exeapi_destroy_kernel_executor(pDevice->pKE);

		CL_DBG_MSG("exeapi_destroy_kernel_executor\n", DBG_END_MSG);

		exeapi_destroy_memory_executor(pDevice->pME);

		CL_DBG_MSG("exeapi_destroy_memory_executor\n", DBG_END_MSG);

		pDevice->pDrv->op->uninit();

		CL_DBG_MSG("pDevice->pDrv->op->uninit\n", DBG_END_MSG);
	}

	free( g_list_device_id );
	free( g_list_rtl_device );

	g_list_device_id = NULL;
	g_list_rtl_device = NULL;

	return CL_SUCCESS;
}

static cl_int
_start_scheduler(cl_rtl_device pDevice)
{
	if (pDevice->bSchedulerStarted == CL_TRUE) return CL_SUCCESS;

	if (CL_HOST_SCHED_TYPE_CENTRAL == pDevice->pDrv->di->scheduler_type)
	{
		schapi_start_central_scheduler(pDevice);
	}
	else if(CL_HOST_SCHED_TYPE_DISTRIBUTED == pDevice->pDrv->di->scheduler_type)
	{
		schapi_start_distributed_scheduler(pDevice);
	}
	else
	{
		printf("ERROR : Unknown scheduler type.\n");
		return CL_ERROR;
	}

	pDevice->bSchedulerStarted = CL_TRUE;
	return CL_SUCCESS;
}


//////////////////////////////////////////////////////////////
// GLOBAL FUNCTION
//////////////////////////////////////////////////////////////
cl_int
devapi_init_dev()
{
	int	idx = 0;

	ancapi_print_platform_begin_msg();

	if( CL_SUCCESS != _init_device_list(g_opencl_host_driver_list, &g_list_rtl_device, &g_list_device_id))
	{
		return CL_ERROR;
	}

	while(NULL != g_opencl_host_driver_list[idx])
	{
		_add_device(g_opencl_host_driver_list[idx]);
		idx++;
	}

	_runtime_thread_affinity();

	ancapi_print_platform_end_msg();

	_devapi_init_device = TRUE;

	return CL_SUCCESS;
}

void
devapi_uninit_dev()
{
	_remove_device_all();
}

cl_int
devapi_get_added_dev_count()
{
	if(FALSE == _devapi_init_device)
	{
		devapi_init_dev();
	}

	return _rtl_added_device_count;
}

cl_int
devapi_find_dev_in_list( cl_device_id dev_id, cl_device_id* dev_id_list, size_t count)
{
	cl_int i;

	for(i=0; i<count; i++)
	{
		if(dev_id == dev_id_list[i])
		{
			return i;
		}
	}

	return -1;
}

cl_bool
devapi_is_valid_dev( cl_device_id dev_id)
{
//	return devapi_find_dev_in_list(dev_id, &g_list_device_id, _rtl_added_device_count) != -1;
	cl_int i;

	for (i = 0; i < _rtl_added_device_count; i++)
	{
		if (dev_id == &g_list_device_id[i]) return CL_TRUE;
	}
	return CL_FALSE;
}

cl_bool
devapi_contains_invalid_dev( cl_device_id* dev_id_list, size_t count)
{
	size_t i;
	for (i = 0; i < count; i++)
	{
		if (!devapi_is_valid_dev(dev_id_list[i]))
		{
			return CL_TRUE;
		}
	}
	return CL_FALSE;
}

cl_int
devapi_get_list_device_id_from_type(cl_device_type type, cl_device_id** pdid_list)
{
	cl_rtl_device pDevice;
	cl_device_type match_dev_type;
	cl_device_id* did_list;
	cl_int num_devices = 0;
	cl_int i=0;

	if(FALSE == _devapi_init_device)
	{
		devapi_init_dev();
	}

	if( 0 == _rtl_added_device_count)
	{
		return 0;
	}

	//find type-matched device count.
	while (NULL != g_list_device_id[i].pobj)
	{
		pDevice = hdlapi_get_obj(cl_rtl_device, &g_list_device_id[i]);
		match_dev_type = pDevice->pDrv->di->qi.dev_type & type;
		
		if ( match_dev_type )
		{
			num_devices++;
		}

		i++;
	}

	if(0 == num_devices)
	{
		return 0;
	}

	//find type-matched device.
	did_list = (cl_device_id*)malloc(num_devices * sizeof(cl_device_id));

	CL_DBG_ASSERT(did_list);

	num_devices = 0;
	i=0;

	while (NULL != g_list_device_id[i].pobj)
	{
		pDevice = hdlapi_get_obj(cl_rtl_device, &g_list_device_id[i]);
		match_dev_type = pDevice->pDrv->di->qi.dev_type & type;
		
		if ( match_dev_type )
		{
			did_list[num_devices++] = &g_list_device_id[i];
			_start_scheduler(pDevice);
		}

		i++;
	}

	*pdid_list = did_list;

	return num_devices;
}

int
devapi_dmm_add_mem(cl_rtl_compute_unit	pCU, cl_rtl_mem pMem)
{
	if(pCU->dmm_slot_count == pCU->dmm_slot_idx)
	{
		//expand dmm_list
		size_t	expandedSlotCount = pCU->dmm_slot_count + pCU->dmm_expand_unit_count;
		char* pExpandedSlot = (char*)malloc(expandedSlotCount * sizeof(cl_rtl_mem));
		if(NULL == pExpandedSlot)
		{
			return CL_ERROR;
		}

		memcpy( pExpandedSlot, (char*)(pCU->dmm_slot), (pCU->dmm_slot_count * sizeof(cl_rtl_mem)) );
		memset( pExpandedSlot + (pCU->dmm_slot_count * sizeof(cl_rtl_mem)), 0, (pCU->dmm_expand_unit_count * sizeof(cl_rtl_mem)) );

		free(pCU->dmm_slot);
		pCU->dmm_slot = (cl_rtl_mem*)pExpandedSlot;
		pCU->dmm_slot_count = expandedSlotCount;
		pCU->dmm_expanded_count++;
	}

	memapi_retain(pMem);

	pCU->dmm_slot[pCU->dmm_slot_idx++] = pMem;

	return CL_SUCCESS;
}

void
devapi_dmm_del_all_mem(cl_rtl_compute_unit	pCU)
{
	cl_rtl_mem		pMem;
	cl_rtl_device	pDev = pCU->pDevice;
	int idx = pCU->idx;
	int i;

	for(i=0; i< pCU->dmm_slot_idx; i++)
	{
		pMem = pCU->dmm_slot[i];
		CL_DBG_ASSERT(NULL != pMem);
		
		if(NULL != pMem->ppDmmTable[pDev->id][idx])
		{
			pDev->pDrv->op->unmap_host_to_dev(pMem->ppDmmTable[pDev->id][idx]);
			pMem->ppDmmTable[pDev->id][idx] = NULL;
		}

		memapi_release(pMem);
		pCU->dmm_slot[i] = NULL;
	}

	if( 0 != pCU->dmm_expanded_count )
	{
		free(pCU->dmm_slot);
		pCU->dmm_slot = malloc(pCU->dmm_expand_unit_count * sizeof(cl_rtl_mem));
		CL_DBG_ASSERT(NULL != pCU->dmm_slot);

		pCU->dmm_expanded_count = 0;
		pCU->dmm_slot_count = pCU->dmm_expand_unit_count;
	}

	pCU->dmm_slot_idx = 0;

	//printf("devapi_dmm_del_all_mem\n");
	//fflush(stdout);
}


//////////////////////////////////////////////////////////////
// OPENCL API
//////////////////////////////////////////////////////////////
CL_API_ENTRY cl_int CL_API_CALL
clGetDeviceIDs(cl_platform_id   platform,
               cl_device_type   device_type, 
               cl_uint          num_entries, 
               cl_device_id *   devices, 
               cl_uint *        num_devices) CL_API_SUFFIX__VERSION_1_0
{
	int i		= 0;
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
		devapi_init_dev();
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

	return CL_SUCCESS;
}


CL_API_ENTRY cl_int CL_API_CALL
clGetDeviceInfo(	cl_device_id	device,
					cl_device_info	param_name,
					size_t			param_value_size,
					void*			param_value,
					size_t*			param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
	pstDEVICE_INFO	pDevInfo;

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

	switch(param_name)
	{
		cmnapi_getinfo(CL_DEVICE_TYPE, cl_device_type, pDevInfo->qi.dev_type);
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
	}

	return CL_SUCCESS;
}
