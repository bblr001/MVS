//***********************************************************
// CreateFileObject所用的文件操作方式控制字(可通过或指令实现多种方式并操作)
#define PCI2312_modeRead          0x0000   // 只读文件方式
#define PCI2312_modeWrite         0x0001   // 只写文件方式
#define	PCI2312_modeReadWrite     0x0002   // 既读又写文件方式
#define PCI2312_modeCreate        0x1000   // 如果文件不存可以创建该文件，如果存在，则重建此文件，并清0

//***********************************************************
#ifndef DEFINING
#define DEVAPI __declspec(dllimport)
#else
#define DEVAPI __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	//################### 常规通用函数(上层底层用户接口)####################
	// 适用于本设备的最基本操作
	DEVAPI HANDLE FAR PASCAL PCI2312_CreateDevice(int DeviceID = 0);  // 创建设备对象
	DEVAPI int FAR PASCAL PCI2312_GetDeviceCount(HANDLE hDevice); // 取得设备总台数
	DEVAPI int FAR PASCAL PCI2312_GetDeviceCurrentID(HANDLE hDevice); // 取得当前设备相应的ID号
	DEVAPI BOOL FAR PASCAL PCI2312_ListDeviceDlg(HANDLE hDevice); // 列表系统当中的所有的该PCI设备
    DEVAPI BOOL FAR PASCAL PCI2312_ReleaseDevice(HANDLE hDevice); // 关闭设备,禁止传输,且释放资源

	//####################### 数字I/O输入输出函数 #################################
	// 用户可以使用WritePortULong和ReadPortULong等函数直接控制寄存器进行I/O
	// 输入输出，但使用下面两个函数更省事，它不需要您关心寄存器分配和位操作等，而只
	// 需象VB等语言的属性操作那么简单地实现各开关量通道的控制。
    DEVAPI BOOL FAR PASCAL PCI2312_SetDeviceDO(             // 输出开关量状态
										HANDLE hDevice,     // 设备句柄								        
										BYTE bDOSts[16]);  // 开关状态
										

	DEVAPI BOOL FAR PASCAL PCI2312_GetDeviceDI(             // 取得开关量状态     
										HANDLE hDevice,     // 设备句柄								        
										BYTE bDISts[16]);  // 开关状态										


	//####################### 外触发中断函数 #################################
	// 它由外界硬件信号DI0的状态变化引起CPU产生中断事件hEventInt。
	// 注意：DI0可由其板上跨接套XF1指定为上升沿还是下降沿产生中断
	// 2-3:下降沿， 1-2:为上升沿
	DEVAPI BOOL FAR PASCAL PCI2312_InitDeviceInt(HANDLE hDevice, HANDLE hEventInt); // 初始化中断
	DEVAPI LONG FAR PASCAL PCI2312_GetDeviceIntCount(HANDLE hDevice);  // 在中断初始化后，用它取得中断服务程序产生的次数
	DEVAPI BOOL FAR PASCAL PCI2312_ReleaseDeviceInt(HANDLE hDevice); // 释放中断资源

	//############### I/O端口直接操作及读写函数(底层用户接口) #####################
	// 适用于用户对本设备更直接、更特殊、更低层、更复杂的控制。比如根据特殊的
	// 控制对象需要特殊的控制流程和控制效率时，则用户可以使用这些接口予以实现。
	// 但这些函数主要适用于传统设备，如ISA总线、并口、串口等设备
	DEVAPI BOOL FAR PASCAL PCI2312_GetDeviceAddr( // 取得指定的指定设备ID号的映射寄存器的线性基地址，返回设备总数
												HANDLE hDevice,  // 设备对象句柄
												PULONG LinearAddr, // 返回指定映射寄存器的线性地址
											    PULONG PhysAddr,   //  返回指定映射寄存器的物理地址												
												int RegisterID);   // 设备映射寄存器的ID号（0-5）
    DEVAPI BOOL FAR PASCAL PCI2312_WritePortByte(HANDLE hDevice, UINT nPort, BYTE Value);
    DEVAPI BOOL FAR PASCAL PCI2312_WritePortWord(HANDLE hDevice, UINT nPort, WORD Value);
    DEVAPI BOOL FAR PASCAL PCI2312_WritePortULong(HANDLE hDevice, UINT nPort, ULONG Value);

    DEVAPI BYTE FAR PASCAL PCI2312_ReadPortByte(HANDLE hDevice, UINT nPort);
    DEVAPI WORD FAR PASCAL PCI2312_ReadPortWord(HANDLE hDevice, UINT nPort);
    DEVAPI ULONG FAR PASCAL PCI2312_ReadPortULong(HANDLE hDevice, UINT nPort);

   	//########################### 文件操作函数 #####################################
    DEVAPI HANDLE FAR PASCAL PCI2312_CreateFileObject(                    // 初始文件系统
										  HANDLE hDevice,     // 设备对象
										  LPCTSTR szNewFileName,  // 新文件名
										  int Mode);		 // 文件操作方式
    
    DEVAPI BOOL FAR PASCAL PCI2312_WriteFile(      // 保存用户空间中数据
										HANDLE hFileObject,  // 设备对象
										PVOID pDataBuffer, // 用户数据空间地址
										ULONG nWriteSizeBytes); // 缓冲区大小(字节)

    DEVAPI BOOL FAR PASCAL PCI2312_ReadFile(  // 读数据
										  HANDLE hFileObject,     // 设备对象
										  PVOID pDataBuffer, // 接受文件数据的用户内存缓冲区
										  ULONG OffsetBytes,   // 从文件前端开始的偏移位置
										  ULONG nReadSizeBytes); // 从偏移位置开始读的字节数

	DEVAPI ULONG FAR PASCAL PCI2312_GetFileLength(HANDLE hFileObject); // 取得指定文件长度（字节）
	DEVAPI BOOL FAR PASCAL PCI2312_SetFileOffset( // 设置文件偏移指针
										  HANDLE hFileObject,   // 文件对象
										  ULONG nOffsetBytes);  // 文件偏移位置（以字为单位）  

    DEVAPI BOOL FAR PASCAL PCI2312_ReleaseFile(HANDLE hFileObject);
    DEVAPI ULONGLONG FAR PASCAL PCI2312_GetDiskFreeBytes(               // 获得指定盘符的磁盘空间
								      LPCTSTR szDiskName);            // 盘符名,如C盘为"C:\\", D盘为"D:\\"

	//################# 线程操作函数 ########################
	DEVAPI HANDLE FAR PASCAL PCI2312_CreateSystemEvent(void); // 创建内核事件对象
	DEVAPI BOOL FAR PASCAL PCI2312_ReleaseSystemEvent(HANDLE hEvent); // 释放内核事件对象
	DEVAPI BOOL FAR PASCAL PCI2312_CreateVBThread(HANDLE *hThread, LPTHREAD_START_ROUTINE StartThread);
    DEVAPI BOOL FAR PASCAL PCI2312_TerminateVBThread(HANDLE hThreadHandle);
	DEVAPI BOOL FAR PASCAL PCI2312_DelayTime(HANDLE hDevice, LONG nTime);  

	//////////////////////////////////////////////////////////////////////////////// 
#ifdef __cplusplus
}
#endif
