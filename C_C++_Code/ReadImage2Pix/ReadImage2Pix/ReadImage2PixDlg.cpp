
// ReadImage2PixDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ReadImage2Pix.h"
#include "ReadImage2PixDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CReadImage2PixDlg 对话框




CReadImage2PixDlg::CReadImage2PixDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReadImage2PixDlg::IDD, pParent)
	,m_ReadImage(L"C:\\Users\\Administrator\\Desktop\\ReadImage2Pix\\res\\lena.bmp")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadImage2PixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReadImage2PixDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CReadImage2PixDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CReadImage2PixDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CReadImage2PixDlg 消息处理程序

BOOL CReadImage2PixDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CReadImage2PixDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CReadImage2PixDlg::OnPaint()
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
HCURSOR CReadImage2PixDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CReadImage2PixDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	ImageData MyImage = m_ReadImage.readIamge2Data();//读取图像到自定义结构体

	//获取设备句柄
	CDC *pDC = GetDC();
	HDC pHDC = pDC->GetSafeHdc();
	//得到当前设备区域
	CRect picRect;
	GetClientRect(&picRect);
	CImage readImage;
	readImage.Load(L"C:\\Users\\Administrator\\Desktop\\ReadImage2Pix\\res\\lena.bmp");
	//显示未处理前图像 
	readImage.Draw(pHDC,30,30,190,250);
	//对图像进行处理(此处进行平均像素值灰度化)
	COLORREF imgColor;
	BYTE rgb[3] = {0},avg = 0;
	for (int x = 0;x < readImage.GetWidth();x++)
	{
		for (int y = 0;y < readImage.GetHeight();y++)
		{
			imgColor = readImage.GetPixel(x,y);
			rgb[0] = GetRValue(imgColor);
			rgb[1] = GetGValue(imgColor);
			rgb[2] = GetBValue(imgColor);
			avg = (rgb[0]+rgb[1]+rgb[2])/3;
			readImage.SetPixel(x,y,RGB(avg,avg,avg));
		}
	}

	//readImage.Draw(pHDC,picRect);
	readImage.Draw(pHDC,290,30,190,250);

	
}


void CReadImage2PixDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate(TRUE);
	//CDialogEx::OnCancel();
}
