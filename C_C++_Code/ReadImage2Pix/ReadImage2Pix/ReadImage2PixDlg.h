
// ReadImage2PixDlg.h : 头文件
//

#pragma once
#include "ReadImage.h"

// CReadImage2PixDlg 对话框
class CReadImage2PixDlg : public CDialogEx
{
// 构造
public:
	CReadImage2PixDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_READIMAGE2PIX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
//数据部分
	CReadImage m_ReadImage;//读取图像类

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
