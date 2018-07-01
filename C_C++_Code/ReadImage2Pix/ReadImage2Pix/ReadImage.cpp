#include "StdAfx.h"
#include "ReadImage.h"


CReadImage::CReadImage(void)
{
}

CReadImage::CReadImage(CString imgFileName)
{
	//类内部变量初始化
	isRleaseAll = false;
	//载入图像
	HRESULT hResult;//
	hResult = m_ReadImagClass.Load(imgFileName);//载入（读取）图像
	if (FAILED(hResult))
		MessageBox(NULL,L"Open Image Bad!",L"Erro",0);
	//获取图像基本信息
	int ImageHeight = 0,ImageWidth = 0,IamgeDepth = 0;
	ImageHeight = m_ReadImagClass.GetHeight();
	ImageWidth = m_ReadImagClass.GetWidth();
	IamgeDepth = m_ReadImagClass.GetBPP() / 8;
	m_ImageData.nHeigth = ImageHeight;
	m_ImageData.nWidth = ImageWidth;
	m_ImageData.Depth = IamgeDepth;
	//生成depth个指向二维数组的指针
	BYTE ***imgDataScr = new BYTE **[IamgeDepth];
	BYTE **pMatrix = NULL;
	if (!imgDataScr)
		MessageBox(NULL,L"calloc Bad!",L"Erro",0);

	for (int i = 0;i < IamgeDepth;i++)
	{
		//生成一个二维数组
		pMatrix = new BYTE *[ImageHeight];
		for (int nHeigth = 0;nHeigth < ImageHeight;nHeigth++)
			pMatrix[nHeigth] = new BYTE[ImageWidth];
		//保存每一个二维指针数组地址
		imgDataScr[i] = pMatrix;
	}
	m_ImageData.imageDataScr = imgDataScr;
}

CReadImage::~CReadImage(void) 
{
	if (!isRleaseAll)  releaseData();
}

ImageData CReadImage::readIamge2Data()
{
	if (m_ReadImagClass.IsNull())
	{
		MessageBox(NULL,L"calloc Bad!",L"Erro",0);
		exit(0);
	}
		
	COLORREF pixel;
	BYTE **pMatrix = NULL;
	BYTE rgb[3]={0};
	int HangLen = m_ImageData.nWidth;
	for (int y = 0;y < m_ImageData.nHeigth;y++)
	{
		for (int x = 0;x <m_ImageData.nWidth;x++)
		{
			pixel = m_ReadImagClass.GetPixel(y,x);
			rgb[0] = GetRValue(pixel);
			rgb[1] = GetGValue(pixel);
			rgb[2] = GetBValue(pixel);
			for (int dpt = 0;dpt < m_ImageData.Depth;dpt++)
			{
				pMatrix = m_ImageData.imageDataScr[dpt];
				pMatrix[y][x] = rgb[dpt];
			}
		}
	}

	return m_ImageData;
}

//释放数组
void CReadImage::releaseData()
{
	BYTE **pMatrix = NULL;
	for (int i = 0;i < m_ImageData.Depth;i++)
	{
		pMatrix = m_ImageData.imageDataScr[i];
		for (int nHeigth = 0;nHeigth < m_ImageData.nHeigth;nHeigth++)
			delete []pMatrix[nHeigth];
		delete []pMatrix;
	}
	delete []m_ImageData.imageDataScr;
	isRleaseAll = true;
}
