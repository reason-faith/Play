
// Play.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Play.h"
#include "PlayDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlayApp

BEGIN_MESSAGE_MAP(CPlayApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPlayApp ����

CPlayApp::CPlayApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CPlayApp ����
CPlayApp theApp;
//HANDLE hMutexA;

// CPlayApp ��ʼ��
BOOL CPlayApp::InitInstance()
{
	//hMutexA = ::CreateMutexA(NULL, FALSE, "{BEB4F89D-78E6-48B2-84B7-C51DE808FDB4}");
	//if (::GetLastError() == ERROR_ALREADY_EXISTS)
	//{
	//	::CloseHandle(hMutexA);
	//	return FALSE;
	//}

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CPlayDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	//CPlayDlg *pDlg = new CPlayDlg();
	//pDlg->Create(IDD_PLAY_DIALOG, 0);
	//pDlg->ShowWindow(SW_HIDE);

	//MSG msg;
	//while (::GetMessageA(&msg, NULL, 0, 0))
	//{
	//	::TranslateMessage(&msg);
	//	::DispatchMessageA(&msg);
	//}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

