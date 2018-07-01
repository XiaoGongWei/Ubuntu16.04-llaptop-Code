#pragma once

typedef struct _ImageData
{
	int nWidth;//ͼ������أ�
	int nHeigth;//ͼ��ߣ����أ�
	int Depth;//ͼ��λ����R��G��B���㣩
	BYTE ***imageDataScr;//�洢1��3ͨ��ͼƬ����ָ�루jpg,png,bmp�ȣ����洢��1��3������
}ImageData;


class CReadImage
{
public:
	CReadImage(void); 
	CReadImage(CString imgFileName);
	ImageData readIamge2Data();//���ͼ���������
	void releaseData();//���õ�ʱ������ñ������ͷ��Ѿ���ȡ������
	~CReadImage(void);
private:
	CImage m_ReadImagClass;//ʹ��MFC�Դ���ȡͼ����
	ImageData m_ImageData;//�洢ͼ���ʽ��Ϣ
	bool isRleaseAll;//����Ƿ��ͷ�����
};

