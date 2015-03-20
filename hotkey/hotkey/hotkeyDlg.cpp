// hotkeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hotkey.h"
#include "hotkeyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_ICON_NOTIFY  WM_USER+5001
#define ID_COPY WM_USER+5002
#define ID_PASTE WM_USER+5003


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// ChotkeyDlg dialog




ChotkeyDlg::ChotkeyDlg(CWnd* pParent /*=NULL*/)
: CDialog(ChotkeyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ChotkeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ChotkeyDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification, "hotkey", IDR_MENU_TRAYICON)
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_COMMAND(ID_HOTKEY_EXIT, &ChotkeyDlg::OnHotkeyExit)
	ON_BN_CLICKED(IDOK, &ChotkeyDlg::OnBnClickedOk)
	ON_WM_CREATE()
	ON_WM_NCPAINT()
	ON_WM_HOTKEY()
END_MESSAGE_MAP()


// ChotkeyDlg message handlers

BOOL ChotkeyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_TRAY); 
	m_trayicon.Create(this, WM_ICON_NOTIFY, "HOTKEY",hIcon,IDR_MENU_TRAYICON);
	if(!::RegisterHotKey(this->m_hWnd,ID_COPY,MOD_CONTROL | MOD_ALT,'C')){
		MessageBox("ctrl+alt+C Register failed");
	}
	if(!::RegisterHotKey(this->m_hWnd,ID_COPY,MOD_CONTROL | MOD_ALT,'V')){
		MessageBox("ctrl+alt+V Register failed");
	}
	//::RegisterHotKey(this->GetSafeHwnd(),ID_PASTE,MOD_CONTROL|MOD_ALT,'v');
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void ChotkeyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void ChotkeyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR ChotkeyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT ChotkeyDlg::OnTrayNotification( WPARAM wParam,LPARAM lParam )
{ 
///	if(LOWORD(lParam) == WM_LBUTTONDBLCLK) 
///	{
///		ShowWindow(SW_SHOW);
///	}
	return m_trayicon.OnTrayNotification(wParam, lParam);
}

void ChotkeyDlg::OnClose()
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	m_trayicon.ShowIcon();
	ShowWindow(SW_HIDE);
	return;
	//CDialog::OnClose();
}

void ChotkeyDlg::OnHotkeyExit()
{
	// TODO: �ڴ�����������������
	UnregisterHotKey(this->m_hWnd, ID_COPY);
	UnregisterHotKey(this->m_hWnd, ID_PASTE);
	OnOK();
}

void ChotkeyDlg::OnBnClickedOk()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	OnOK();
}

int ChotkeyDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ�������ר�õĴ�������

	return 0;
}

void ChotkeyDlg::OnNcPaint()
{
	// TODO: �ڴ˴�������Ϣ�����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnNcPaint()
	static int i = 2;
	if(i > 0)
	{
		i --;
		ShowWindow(SW_HIDE);
	}
	else
		CDialog::OnNcPaint();
}


void ChotkeyDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	if (nHotKeyId == ID_COPY){
	}else if(nHotKeyId == ID_PASTE){
	}

	CDialog::OnHotKey(nHotKeyId, nKey1, nKey2);
}