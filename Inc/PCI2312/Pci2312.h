//***********************************************************
// CreateFileObject���õ��ļ�������ʽ������(��ͨ����ָ��ʵ�ֶ��ַ�ʽ������)
#define PCI2312_modeRead          0x0000   // ֻ���ļ���ʽ
#define PCI2312_modeWrite         0x0001   // ֻд�ļ���ʽ
#define	PCI2312_modeReadWrite     0x0002   // �ȶ���д�ļ���ʽ
#define PCI2312_modeCreate        0x1000   // ����ļ�������Դ������ļ���������ڣ����ؽ����ļ�������0

//***********************************************************
#ifndef DEFINING
#define DEVAPI __declspec(dllimport)
#else
#define DEVAPI __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	//################### ����ͨ�ú���(�ϲ�ײ��û��ӿ�)####################
	// �����ڱ��豸�����������
	DEVAPI HANDLE FAR PASCAL PCI2312_CreateDevice(int DeviceID = 0);  // �����豸����
	DEVAPI int FAR PASCAL PCI2312_GetDeviceCount(HANDLE hDevice); // ȡ���豸��̨��
	DEVAPI int FAR PASCAL PCI2312_GetDeviceCurrentID(HANDLE hDevice); // ȡ�õ�ǰ�豸��Ӧ��ID��
	DEVAPI BOOL FAR PASCAL PCI2312_ListDeviceDlg(HANDLE hDevice); // �б�ϵͳ���е����еĸ�PCI�豸
    DEVAPI BOOL FAR PASCAL PCI2312_ReleaseDevice(HANDLE hDevice); // �ر��豸,��ֹ����,���ͷ���Դ

	//####################### ����I/O����������� #################################
	// �û�����ʹ��WritePortULong��ReadPortULong�Ⱥ���ֱ�ӿ��ƼĴ�������I/O
	// �����������ʹ����������������ʡ�£�������Ҫ�����ļĴ��������λ�����ȣ���ֻ
	// ����VB�����Ե����Բ�����ô�򵥵�ʵ�ָ�������ͨ���Ŀ��ơ�
    DEVAPI BOOL FAR PASCAL PCI2312_SetDeviceDO(             // ���������״̬
										HANDLE hDevice,     // �豸���								        
										BYTE bDOSts[16]);  // ����״̬
										

	DEVAPI BOOL FAR PASCAL PCI2312_GetDeviceDI(             // ȡ�ÿ�����״̬     
										HANDLE hDevice,     // �豸���								        
										BYTE bDISts[16]);  // ����״̬										


	//####################### �ⴥ���жϺ��� #################################
	// �������Ӳ���ź�DI0��״̬�仯����CPU�����ж��¼�hEventInt��
	// ע�⣺DI0��������Ͽ����XF1ָ��Ϊ�����ػ����½��ز����ж�
	// 2-3:�½��أ� 1-2:Ϊ������
	DEVAPI BOOL FAR PASCAL PCI2312_InitDeviceInt(HANDLE hDevice, HANDLE hEventInt); // ��ʼ���ж�
	DEVAPI LONG FAR PASCAL PCI2312_GetDeviceIntCount(HANDLE hDevice);  // ���жϳ�ʼ��������ȡ���жϷ����������Ĵ���
	DEVAPI BOOL FAR PASCAL PCI2312_ReleaseDeviceInt(HANDLE hDevice); // �ͷ��ж���Դ

	//############### I/O�˿�ֱ�Ӳ�������д����(�ײ��û��ӿ�) #####################
	// �������û��Ա��豸��ֱ�ӡ������⡢���Ͳ㡢�����ӵĿ��ơ�������������
	// ���ƶ�����Ҫ����Ŀ������̺Ϳ���Ч��ʱ�����û�����ʹ����Щ�ӿ�����ʵ�֡�
	// ����Щ������Ҫ�����ڴ�ͳ�豸����ISA���ߡ����ڡ����ڵ��豸
	DEVAPI BOOL FAR PASCAL PCI2312_GetDeviceAddr( // ȡ��ָ����ָ���豸ID�ŵ�ӳ��Ĵ��������Ի���ַ�������豸����
												HANDLE hDevice,  // �豸������
												PULONG LinearAddr, // ����ָ��ӳ��Ĵ��������Ե�ַ
											    PULONG PhysAddr,   //  ����ָ��ӳ��Ĵ����������ַ												
												int RegisterID);   // �豸ӳ��Ĵ�����ID�ţ�0-5��
    DEVAPI BOOL FAR PASCAL PCI2312_WritePortByte(HANDLE hDevice, UINT nPort, BYTE Value);
    DEVAPI BOOL FAR PASCAL PCI2312_WritePortWord(HANDLE hDevice, UINT nPort, WORD Value);
    DEVAPI BOOL FAR PASCAL PCI2312_WritePortULong(HANDLE hDevice, UINT nPort, ULONG Value);

    DEVAPI BYTE FAR PASCAL PCI2312_ReadPortByte(HANDLE hDevice, UINT nPort);
    DEVAPI WORD FAR PASCAL PCI2312_ReadPortWord(HANDLE hDevice, UINT nPort);
    DEVAPI ULONG FAR PASCAL PCI2312_ReadPortULong(HANDLE hDevice, UINT nPort);

   	//########################### �ļ��������� #####################################
    DEVAPI HANDLE FAR PASCAL PCI2312_CreateFileObject(                    // ��ʼ�ļ�ϵͳ
										  HANDLE hDevice,     // �豸����
										  LPCTSTR szNewFileName,  // ���ļ���
										  int Mode);		 // �ļ�������ʽ
    
    DEVAPI BOOL FAR PASCAL PCI2312_WriteFile(      // �����û��ռ�������
										HANDLE hFileObject,  // �豸����
										PVOID pDataBuffer, // �û����ݿռ��ַ
										ULONG nWriteSizeBytes); // ��������С(�ֽ�)

    DEVAPI BOOL FAR PASCAL PCI2312_ReadFile(  // ������
										  HANDLE hFileObject,     // �豸����
										  PVOID pDataBuffer, // �����ļ����ݵ��û��ڴ滺����
										  ULONG OffsetBytes,   // ���ļ�ǰ�˿�ʼ��ƫ��λ��
										  ULONG nReadSizeBytes); // ��ƫ��λ�ÿ�ʼ�����ֽ���

	DEVAPI ULONG FAR PASCAL PCI2312_GetFileLength(HANDLE hFileObject); // ȡ��ָ���ļ����ȣ��ֽڣ�
	DEVAPI BOOL FAR PASCAL PCI2312_SetFileOffset( // �����ļ�ƫ��ָ��
										  HANDLE hFileObject,   // �ļ�����
										  ULONG nOffsetBytes);  // �ļ�ƫ��λ�ã�����Ϊ��λ��  

    DEVAPI BOOL FAR PASCAL PCI2312_ReleaseFile(HANDLE hFileObject);
    DEVAPI ULONGLONG FAR PASCAL PCI2312_GetDiskFreeBytes(               // ���ָ���̷��Ĵ��̿ռ�
								      LPCTSTR szDiskName);            // �̷���,��C��Ϊ"C:\\", D��Ϊ"D:\\"

	//################# �̲߳������� ########################
	DEVAPI HANDLE FAR PASCAL PCI2312_CreateSystemEvent(void); // �����ں��¼�����
	DEVAPI BOOL FAR PASCAL PCI2312_ReleaseSystemEvent(HANDLE hEvent); // �ͷ��ں��¼�����
	DEVAPI BOOL FAR PASCAL PCI2312_CreateVBThread(HANDLE *hThread, LPTHREAD_START_ROUTINE StartThread);
    DEVAPI BOOL FAR PASCAL PCI2312_TerminateVBThread(HANDLE hThreadHandle);
	DEVAPI BOOL FAR PASCAL PCI2312_DelayTime(HANDLE hDevice, LONG nTime);  

	//////////////////////////////////////////////////////////////////////////////// 
#ifdef __cplusplus
}
#endif
