#include <pspsdk.h>
#include <string.h>
//#include <pspidstorage.h>
#include <pspsysmem_kernel.h>

PSP_MODULE_INFO("kernel", 0x1006, 0, 4);
PSP_MAIN_THREAD_ATTR(0);

int pspKernelGetModel(void)
{
	int generation = 0;
	int k1 = pspSdkSetK1(0);
	generation = sceKernelGetModel()+1;
	pspSdkSetK1(k1);

	return generation;
}

//void pspIdStorageLookup(u16 key, u32 offset, void *buf, u32 len)
//{
//	int k1 = pspSdkSetK1(0);
//	memset(buf, 0, len);
//	sceIdStorageLookup(key, offset, buf, len);
//	pspSdkSetK1(k1);
//}

int module_start(SceSize args, void *argp)
{
	return 0;
}

int module_stop(void)
{
	return 0;
}
