#include <pspkernel.h>
#include <pspctrl.h> // sceCtrlReadBufferPositive
#include <pspreg.h> // sceReg*
#include <string.h> // memset/strlen/strcpy
#include <pspsdk.h> // pspSdkLoadStartModule

PSP_MODULE_INFO("fakepair", 0, 4, 0);
PSP_MAIN_THREAD_ATTR(0);
PSP_HEAP_SIZE_KB(20480);

#define printf pspDebugScreenPrintf

int pspKernelGetModel(void);
void pspIdStorageLookup(u16 key, u32 offset, void *buf, u32 len);

int main(int argc, char*argv[])
{
	int i;
	int ret;
	int model;
//	SceUID f;
	SceUID uid;
	SceCtrlData pad;
    struct RegParam rpar;
//	unsigned char mac[6];
	unsigned char text[64];
    REGHANDLE rhan, rhnd, rhdl;
	unsigned int data, type, size;
	char device_name[32] = "FakeShock®3";

	pspDebugScreenInit();
	pspDebugScreenClear(); // îñîáî íå íóæíî
	printf(" PSPgo Fake-Pair Tool v0.4 by Yoti\n\n");

	uid = pspSdkLoadStartModule("kernel.prx", PSP_MEMORY_PARTITION_KERNEL);
	if (uid < 0)
	{
		printf("pspSdkLoadStartModule: 0x%08x\n", uid);
		sceKernelDelayThread(3.00*1000*1000);
		sceKernelExitGame();
	}

	model = pspKernelGetModel();
	if (model != 5)
	{
		printf("pspKernelGetModel: 0x%08x\n", model);
		sceKernelDelayThread(3.00*1000*1000);
		sceKernelExitGame();
	}
		
    memset(&rpar, 0, sizeof(rpar));
    rpar.regtype = 1;
    rpar.namelen = strlen("/system");
    rpar.unk2 = 1;
    rpar.unk3 = 1;
    strcpy(rpar.name, "/system");

	ret = sceRegOpenRegistry(&rpar, 2, &rhan);
	if (ret == 0)
	{
		ret = sceRegOpenCategory(rhan, "/CONFIG/BT/DEVICE0", 2, &rhnd); // slot 0, valid 0-7
		if (ret == 0)
		{
			ret = sceRegGetKeyInfo(rhnd, "device_type", &rhdl, &type, &size);
			if (ret == 0)
			{
				/*
				data
					0 - no device
					1 - dualshock
					2 - empty val
					3 - cellphone
					4 - audio
					5 - audio
					6 - audio
					7 - empty val
					8 - audio
					9 - empty val
				*/
				data = 1;
				ret = sceRegSetKeyValue(rhnd, "device_type", &data, size);
				if (ret == 0)
					printf("FakeShock(R)3 t-param was written at slot 0\n");
				else
					printf("sceRegSetKeyValue: 0x%08x\n", ret);
			}
			else
				printf("sceRegGetKeyInfo: 0x%08x\n", ret);
			//
//			ret = sceRegGetKeyInfo(rhnd, "device_name", &rhdl, &type, &size);
//			if (ret == 0)
//			{
//				memset(&text, 0, sizeof(text));
//				ret = sceRegGetKeyValue(rhnd, rhdl, text, size);
//				if (ret == 0)
//				{
//					f = sceIoOpen("backup.name", PSP_O_WRONLY | PSP_O_CREAT, 0777);
//					if (f >= 0)
//						sceIoWrite(f, text, size);
//					sceIoClose(f);
//				}	
//				else
//					printf("sceRegGetKeyValue: 0x%08x\n", ret);
//			}
//			else
//				printf("sceRegGetKeyInfo: 0x%08x\n", ret);
			//
			ret = sceRegGetKeyInfo(rhnd, "device_name", &rhdl, &type, &size);
			if (ret == 0)
			{
				memset(&text, 0, sizeof(text));
				for (i = 0; i < strlen(device_name); i++)
					text[i*2] = device_name[i];
				ret = sceRegSetKeyValue(rhnd, "device_name", text, size);
				if (ret == 0)
					printf("FakeShock(R)3 n-param was written at slot 0\n");
				else
					printf("sceRegSetKeyValue: 0x%08x\n", ret);
			}
			else
				printf("sceRegGetKeyInfo: 0x%08x\n", ret);
		}
		else
			printf("sceRegOpenCategory: 0x%08x\n", ret);
		sceRegFlushCategory(rhnd);
		sceRegCloseCategory(rhnd);
	}
	else
		printf("sceRegOpenRegistry: 0x%08x\n", ret);
	sceRegFlushRegistry(rhan);
	sceRegCloseRegistry(rhan);

//	pspIdStorageLookup(0x50, 0x41, &mac, 6);
//	printf("PSP side is done. Reprogram your DS3 from PC or Android.\n");
//	printf("BlueTooth MAC of this PSPgo system is %02x:%02x:%02x:%02x:%02x:%02x.\n",
//			mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

	printf("\n Press X to exit...\n");
	do
	{
		sceCtrlReadBufferPositive(&pad, 1);
		sceKernelDelayThread(0.05*1000*1000);
	}
	while(!(pad.Buttons & PSP_CTRL_CROSS));
	sceKernelExitGame();

	return 0;
}