#include "CL/cl.h"
int main(){
	cl_int err;
	cl_platform_id platform_id;
	cl_uint num_of_platforms=0;

	// retreives a list of platfoms available
	if(clGetPlatformIDs(1, &platform_id, &num_of_platforms) != CL_SUCCESS)
	{
		printf("Unable to get platform_id\n");
		return 1;
	}
	
	char buffer[1024];
	clGetPlatformInfo(platform_id, CL_PLATFORM_PROFILE,    sizeof(buffer), buffer, NULL);
	printf("PROFILE    = %s\n", buffer);
        clGetPlatformInfo(platform_id, CL_PLATFORM_VERSION,    sizeof(buffer), buffer, NULL);
        printf("VERSION    = %s\n", buffer);
        clGetPlatformInfo(platform_id, CL_PLATFORM_NAME,       sizeof(buffer), buffer, NULL);
        printf("NAME       = %s\n", buffer);
        clGetPlatformInfo(platform_id, CL_PLATFORM_VENDOR,     sizeof(buffer), buffer, NULL);
        printf("VENDOR     = %s\n", buffer);
        clGetPlatformInfo(platform_id, CL_PLATFORM_EXTENSIONS, sizeof(buffer), buffer, NULL);
        printf("EXTENSIONS = %s\n", buffer);



	return 0;
}

