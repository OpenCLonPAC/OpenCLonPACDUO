#define cmnapi_getinfo_array(param,type,value,length)	\
case param:													\
{															\
	size_t size = sizeof(type) * length;					\
	if (param_value)										\
	{														\
		if (param_value_size < size)						\
			return CL_INVALID_VALUE;						\
		memcpy(param_value, value, size);					\
	}														\
	if (param_value_size_ret) *param_value_size_ret = size;	\
	break;													\
}

#define cmnapi_getinfo_default()						\
default: return CL_INVALID_VALUE;
