
// ReadImage2PixDlg.h : ͷ�ļ�
//

#pragma once
#include "ReadImage.h"

// CReadImage2PixDlg �Ի���
class CReadImage2PixDlg : public CDialogEx
{
// ����
public:
	CReadImage2PixDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_READIMAGE2PIX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
//���ݲ���
	CReadImage m_ReadImage;//��ȡͼ����

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
