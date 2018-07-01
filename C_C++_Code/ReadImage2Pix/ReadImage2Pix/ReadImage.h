#pragma once

typedef struct _ImageData
{
	int nWidth;//图像宽（像素）
	int nHeigth;//图像高（像素）
	int Depth;//图像位数（R、G、B三层）
	BYTE ***imageDataScr;//存储1或3通道图片数据指针（jpg,png,bmp等），存储了1或3个矩阵
}ImageData;


class CReadImage
{
public:
	CReadImage(void); 
	CReadImage(CString imgFileName);
	ImageData readIamge2Data();//获得图像矩阵数据
	void releaseData();//不用的时候请调用本函数释放已经读取的数据
	~CReadImage(void);
private:
	CImage m_ReadImagClass;//使用MFC自带读取图像类
	ImageData m_ImageData;//存储图像格式信息
	bool isRleaseAll;//标记是否释放数据
};

