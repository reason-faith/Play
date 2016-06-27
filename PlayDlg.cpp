
// PlayDlg.cpp : 实现文件
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


// CPlayDlg 对话框




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


// CPlayDlg 消息处理程序

BOOL CPlayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);								// 设置大图标
	SetIcon(m_hIcon, FALSE);							// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//SetWindowPos(&CWnd::wndNoTopMost,0,1,0,0,SWP_HIDEWINDOW);
	//ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	//ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);//从任务栏中去掉.
	//SetWindowPos(&wndTop,0,1,0,0,NULL);

	/*WINDOWPLACEMENT wp;
	wp.length = sizeof(WINDOWPLACEMENT);
	wp.flags = WPF_RESTORETOMAXIMIZED;
	wp.showCmd = SW_HIDE;
	SetWindowPlacement(&wp);*/

	this->SetWindowTextA("Play");

	//this->SetTimer(NULL, 500, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPlayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPlayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


WORD wMCIDeviceID = 0;

afx_msg LRESULT CPlayDlg::OnPlayPrompt(WPARAM wParam, LPARAM lParam)
{
	// FILE *fp = fopen("d:\\PlayPrompt.txt", "wt");
	// fprintf(fp, "收到进程外消息.\n");
	// fclose(fp);

	if (wParam == 0)
	{
		if (wMCIDeviceID != 0)												
		{
			mciSendCommand(wMCIDeviceID, MCI_CLOSE, MCI_WAIT, NULL);
			wMCIDeviceID = 0;
		}

	}
	// 学生队列不为空，提示音效处于播放状态(无需进行任何处理) 处于非播放状态(开始播放)
	else
	{	
		if (wMCIDeviceID != 0)								//当前处于播放状态
		{
			return 0;
		}
		else															//当前处于静音状态
		{
			MCI_OPEN_PARMS open = {0};										
			open.lpstrElementName = ".\\resources\\prompt.mp3";			//指定播放文件路径  
			open.lpstrDeviceType = "mpegvideo";							//指定播放设备  

			DWORD dwError;
			char errorText[128];										//定义错误信息  
			dwError = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE|MCI_OPEN_ELEMENT|MCI_WAIT, (DWORD)(LPVOID)&open);	//初始化音频设备  

			if (dwError == 0)  
			{  
				//保存打开设备的设备ID
				wMCIDeviceID = open.wDeviceID;

				//play命令消息参数结构体
				MCI_PLAY_PARMS play;  
				play.dwFrom = 0;  
				play.dwCallback = NULL; 

				//重复播放
				mciSendCommand(wMCIDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)&play);  
			}  
			else  
			{  
				mciGetErrorString(dwError, (LPSTR)errorText, 128);
				this->MessageBox("无法检测到音频播放设备，请插入耳麦.", "提示信息");  
			}
		}
	}

	return 0;
}


void CPlayDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->ShowWindow(SW_HIDE);
	this->KillTimer(NULL);
	CDialogEx::OnTimer(nIDEvent);
}

//extern HANDLE hMutexA;
void CPlayDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//::CloseHandle(hMutexA);
	CDialogEx::OnClose();
}


void CPlayDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanging(lpwndpos);
	
	// TODO: 在此处添加消息处理程序代码
	lpwndpos->flags &= SWP_HIDEWINDOW;
}
