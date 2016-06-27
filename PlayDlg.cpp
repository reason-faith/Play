
// PlayDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Play.h"
#include "PlayDlg.h"
#include "afxdialogex.h"
#include <MMSystem.h>		
#pragma comment(lib, "winmm.lib")
#include <Digitalv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlayDlg �Ի���




CPlayDlg::CPlayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPlayDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPlayDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_PLAY_PROMPT, &CPlayDlg::OnPlayPrompt)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


// CPlayDlg ��Ϣ�������

BOOL CPlayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);								// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);							// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//SetWindowPos(&CWnd::wndNoTopMost,0,1,0,0,SWP_HIDEWINDOW);
	//ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	//ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);//����������ȥ��.
	//SetWindowPos(&wndTop,0,1,0,0,NULL);

	/*WINDOWPLACEMENT wp;
	wp.length = sizeof(WINDOWPLACEMENT);
	wp.flags = WPF_RESTORETOMAXIMIZED;
	wp.showCmd = SW_HIDE;
	SetWindowPlacement(&wp);*/

	this->SetWindowTextA("Play");

	//this->SetTimer(NULL, 500, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPlayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPlayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


WORD wMCIDeviceID = 0;

afx_msg LRESULT CPlayDlg::OnPlayPrompt(WPARAM wParam, LPARAM lParam)
{
	// FILE *fp = fopen("d:\\PlayPrompt.txt", "wt");
	// fprintf(fp, "�յ���������Ϣ.\n");
	// fclose(fp);

	if (wParam == 0)
	{
		if (wMCIDeviceID != 0)												
		{
			mciSendCommand(wMCIDeviceID, MCI_CLOSE, MCI_WAIT, NULL);
			wMCIDeviceID = 0;
		}

	}
	// ѧ�����в�Ϊ�գ���ʾ��Ч���ڲ���״̬(��������κδ���) ���ڷǲ���״̬(��ʼ����)
	else
	{	
		if (wMCIDeviceID != 0)								//��ǰ���ڲ���״̬
		{
			return 0;
		}
		else															//��ǰ���ھ���״̬
		{
			MCI_OPEN_PARMS open = {0};										
			open.lpstrElementName = ".\\resources\\prompt.mp3";			//ָ�������ļ�·��  
			open.lpstrDeviceType = "mpegvideo";							//ָ�������豸  

			DWORD dwError;
			char errorText[128];										//���������Ϣ  
			dwError = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE|MCI_OPEN_ELEMENT|MCI_WAIT, (DWORD)(LPVOID)&open);	//��ʼ����Ƶ�豸  

			if (dwError == 0)  
			{  
				//������豸���豸ID
				wMCIDeviceID = open.wDeviceID;

				//play������Ϣ�����ṹ��
				MCI_PLAY_PARMS play;  
				play.dwFrom = 0;  
				play.dwCallback = NULL; 

				//�ظ�����
				mciSendCommand(wMCIDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)&play);  
			}  
			else  
			{  
				mciGetErrorString(dwError, (LPSTR)errorText, 128);
				this->MessageBox("�޷���⵽��Ƶ�����豸����������.", "��ʾ��Ϣ");  
			}
		}
	}

	return 0;
}


void CPlayDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	this->ShowWindow(SW_HIDE);
	this->KillTimer(NULL);
	CDialogEx::OnTimer(nIDEvent);
}

//extern HANDLE hMutexA;
void CPlayDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//::CloseHandle(hMutexA);
	CDialogEx::OnClose();
}


void CPlayDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanging(lpwndpos);
	
	// TODO: �ڴ˴������Ϣ����������
	lpwndpos->flags &= SWP_HIDEWINDOW;
}
