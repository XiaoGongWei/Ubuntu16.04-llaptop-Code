
// ReadImage2PixDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReadImage2Pix.h"
#include "ReadImage2PixDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CReadImage2PixDlg �Ի���




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


// CReadImage2PixDlg ��Ϣ�������

BOOL CReadImage2PixDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CReadImage2PixDlg::OnPaint()
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
HCURSOR CReadImage2PixDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CReadImage2PixDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	ImageData MyImage = m_ReadImage.readIamge2Data();//��ȡͼ���Զ���ṹ��

	//��ȡ�豸���
	CDC *pDC = GetDC();
	HDC pHDC = pDC->GetSafeHdc();
	//�õ���ǰ�豸����
	CRect picRect;
	GetClientRect(&picRect);
	CImage readImage;
	readImage.Load(L"C:\\Users\\Administrator\\Desktop\\ReadImage2Pix\\res\\lena.bmp");
	//��ʾδ����ǰͼ�� 
	readImage.Draw(pHDC,30,30,190,250);
	//��ͼ����д���(�˴�����ƽ������ֵ�ҶȻ�)
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Invalidate(TRUE);
	//CDialogEx::OnCancel();
}
