//***********************************************************
// CreateFileObject所用的文件操作方式控制字(可通过或指令实现多种方式并操作)
#define PCI2003_modeRead          0x0000   // 只读文件方式
#define PCI2003_modeWrite         0x0001   // 只写文件方式
#define	PCI2003_modeReadWrite     0x0002   // 既读又写文件方式
#define PCI2003_modeCreate        0x1000   // 如果文件不存可以创建该文件，如果存在，则重建此文件，并清0




#ifndef DEFINING
#define DEVAPI __declspec(dllimport)
#else
#define DEVAPI __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	//######################## 常规通用函数 #################################
	// 适用于本设备的最基本操作
	DEVAPI HANDLE FAR PASCAL CommUser_CreateDevice(void);  // 创建设备对象
	DEVAPI int FAR PASCAL CommUser_FindPCIDevice( // 寻找指定的PCI设备，并返回设备总台数
		                                          HANDLE hDevice, // 设备对象句柄
		                                          WORD VendorID,  // 厂商ID号(请从我公司或代理商索取)
												  WORD DeviceID ); // 设备ID号（与设备型号中的数字匹配，如PCI2000, 则为2000H，　PCI2002则为2002H）
    DEVAPI BOOL FAR PASCAL CommUser_ReleaseDevice(HANDLE hDevice); // 关闭设备,禁止传输,且释放资源	
	
	//################# I/O端口直接操作及读写函数 ########################
	// 适用于用户对本设备更直接、更特殊、更低层、更复杂的控制。比如根据特殊的
	// 控制对象需要特殊的控制流程和控制效率时，则用户可以使用这些接口予以实现。
	// 但这些函数主要适用于传统设备，如ISA总线、并口、串口等设备，不能用于本PCI设备
    DEVAPI BOOL FAR PASCAL CommUser_WritePortByte(HANDLE hDevice, UINT nPort, BYTE Value);
    DEVAPI BOOL FAR PASCAL CommUser_WritePortWord(HANDLE hDevice, UINT nPort, WORD Value);
    DEVAPI BOOL FAR PASCAL CommUser_WritePortULong(HANDLE hDevice, UINT nPort, ULONG Value);

    DEVAPI BYTE FAR PASCAL CommUser_ReadPortByte(HANDLE hDevice, UINT nPort);
    DEVAPI WORD FAR PASCAL CommUser_ReadPortWord(HANDLE hDevice, UINT nPort);
    DEVAPI ULONG FAR PASCAL CommUser_ReadPortULong(HANDLE hDevice, UINT nPort);



   	//################# 辅助函数 ########################
    // 文件操作函数
    DEVAPI HANDLE FAR PASCAL CommUser_CreateFileObject(                    // 初始文件系统
										  HANDLE hDevice,     // 设备对象
										  LPCTSTR NewFileName,  // 新文件名
										  int Mode);		 // 文件操作方式    
    DEVAPI BOOL FAR PASCAL CommUser_WriteFile(      // 保存用户空间中数据
										HANDLE hFileObject,  // 设备对象
										PWORD pUserRegion, // 用户数据空间地址
										ULONG nWriteSizeBytes); // 缓冲区大小(字节)

    DEVAPI BOOL FAR PASCAL CommUser_ReadFile(  // 读数据
										  HANDLE hFileObject,     // 设备对象
										  PWORD pFileUserRegion, // 接受文件数据的用户内存缓冲区
										  ULONG OffsetBytes,   // 从文件前端开始的偏移位置
										  ULONG nReadSizeBytes); // 从偏移位置开始读的字节数

	DEVAPI ULONG FAR PASCAL CommUser_GetFileLength(HANDLE hFileObject); // 取得指定文件长度（字节）
    DEVAPI BOOL FAR PASCAL CommUser_ReleaseFile(HANDLE hFileObject); // 释放文件对象

    DEVAPI ULONG FAR PASCAL CommUser_GetDiskFreeBytes(               // 获得指定盘符的磁盘空间
								      LPCTSTR DiskName);            // 盘符名,如C盘为"C:\\", D盘为"D:\\"

    
    // 线程管理函数（主要基于Visual Basic）
	DEVAPI HANDLE FAR PASCAL CommUser_CreateSystemEvent(void); // 创建内核事件对象，供InitDeviceInt等函数使用
	DEVAPI BOOL FAR PASCAL CommUser_CreateVBThread(HANDLE *hThread, LPTHREAD_START_ROUTINE StartThread);
    DEVAPI BOOL FAR PASCAL CommUser_TerminateVBThread(HANDLE hThreadHandle);

    // 数据类型转换(主要用于Delphi)
	DEVAPI ULONG FAR PASCAL CommUser_FloatToInt(float SourceData);
    // 极速数据排序函数
	DEVAPI void FAR PASCAL CommUser_QuickSortDataByte(PBYTE data,LONG left,LONG right);  // left=0时，为缓冲区起点，right为缓冲区终点，通常为数据总点数减1
	DEVAPI void FAR PASCAL CommUser_QuickSortDataWord(PWORD data,LONG left,LONG right);  // left=0时，为缓冲区起点，right为缓冲区终点，通常为数据总点数减1
	DEVAPI void FAR PASCAL CommUser_QuickSortDataULong(PULONG data,LONG left,LONG right);  // left=0时，为缓冲区起点，right为缓冲区终点，通常为数据总点数减1
    ///////////////////////////////////////////////////////////////////////////////// 
#ifdef __cplusplus
}
#endif
