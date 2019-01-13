// EnterChannelDlg.cpp : implement file
//

#include "stdafx.h"
#include "OpenLive.h"
#include "EnterChannelDlg.h"


#include "afxdialogex.h"


// CEnterChannelDlg Dialog

IMPLEMENT_DYNAMIC(CEnterChannelDlg, CDialogEx)

CEnterChannelDlg::CEnterChannelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEnterChannelDlg::IDD, pParent)
{
    
}

CEnterChannelDlg::~CEnterChannelDlg()
{

}

void CEnterChannelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDCHNAME_CHANNEL, m_ctrChannel);
	DDX_Control(pDX, IDC_BTNTEST_CHANNEL, m_btnTest);
	DDX_Control(pDX, IDC_BTNJOIN_CHANNEL, m_btnJoin);
	DDX_Control(pDX, IDC_BTNSET_CHANNEL, m_btnSetup);
	DDX_Control(pDX, IDC_EDCHPSWD_CHANNEL, m_ctrPassword);
	DDX_Control(pDX, IDC_BTN_RTMP, m_btnRTMP);
	DDX_Control(pDX, IDC_ED_CDNNUMBER, m_edtCdnNumber);
	DDX_Control(pDX, IDC_CHECK_SELF_VIDEOPROFILE, m_chkSelfDefineVideoProfile);
	DDX_Control(pDX, IDC_RESOLUTION_WIDTH, m_edtResolutionWidth);
	DDX_Control(pDX, IDC_RESOLUTION_HEIGHT, m_edtResolutionHeight);
	DDX_Control(pDX, IDC_VIDEO_FPS, m_edtVideoFPS);
	DDX_Control(pDX, IDC_VIDEO_BITRATE, m_edtVideoBitrate);
}


BEGIN_MESSAGE_MAP(CEnterChannelDlg, CDialogEx)
	ON_WM_NCHITTEST()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTNTEST_CHANNEL, &CEnterChannelDlg::OnBnClickedBtntestChannel)
	ON_BN_CLICKED(IDC_BTNJOIN_CHANNEL, &CEnterChannelDlg::OnBnClickedBtnjoinChannel)
	ON_BN_CLICKED(IDC_BTNSET_CHANNEL, &CEnterChannelDlg::OnBnClickedBtnsetChannel)
	ON_CBN_SELCHANGE(IDC_CMBROLE_CHANNEL, &CEnterChannelDlg::OnCbnSelchangeCmbRole)
	ON_BN_CLICKED(IDC_BTN_RTMP, &CEnterChannelDlg::OnBnClickedBtnRtmp)
	ON_BN_CLICKED(IDC_CHECK_SELF_VIDEOPROFILE, &CEnterChannelDlg::OnBnClickedCheckSelfVideoprofile)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CEnterChannelDlg Message Handler
BOOL CEnterChannelDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN){
		switch (pMsg->wParam){
		case VK_ESCAPE:
			return FALSE;
		case VK_RETURN:
			OnBnClickedBtnjoinChannel();
			return FALSE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL CEnterChannelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ftHead.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	m_ftDesc.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	m_ftBtn.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	m_penFrame.CreatePen(PS_SOLID, 1, RGB(0xD8, 0xD8, 0xD8));

	m_dlgDevice.Create(CDeviceDlg::IDD, this);
	m_dlgDevice.EnableDeviceTest(TRUE);

	SetBackgroundColor(RGB(0xFF, 0xFF, 0xFF));
	InitCtrls();
	ShowSelfEdit(false);
	//InitSelfEdit();
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEnterChannelDlg::InitCtrls()
{
	CRect ClientRect;

	GetClientRect(&ClientRect);
	m_ctrChannel.MoveWindow(ClientRect.Width() / 2 - 150 , 33 , 300 , 22, TRUE);
    m_ctrChannel.SetFont(&m_ftDesc);
	m_ctrChannel.SetCaretPos(CPoint(12, 148));
	m_ctrChannel.ShowCaret();
	m_ctrChannel.SetTip(LANG_STR("IDS_CHN_CHANNELNAME"));

	m_edtCdnNumber.SetTip(LANG_STR("IDS_CHN_CDNNUMBER"));
    
	m_ctrPassword.MoveWindow(ClientRect.Width() / 2 - 150 , 82 , 120 , 22, TRUE);
	m_ctrPassword.SetTip(LANG_STR("IDS_CHN_ROOMPASSWORD"));

	m_ctrRole.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE, CRect(ClientRect.Width() / 2 + 1, 168, 180, 32), this, IDC_CMBROLE_CHANNEL);
	
	m_ctrRole.MoveWindow(ClientRect.Width() / 2 + 40, 78, 130 , 22, TRUE);
	m_ctrRole.SetFont(&m_ftHead);
	m_ctrRole.SetButtonImage(IDB_CMBBTN, 12, 12, RGB(0xFF, 0x00, 0xFF));
	m_ctrRole.SetFaceColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_ctrRole.InsertString(0, LANG_STR("IDS_CHN_CASTER"));
	m_ctrRole.InsertString(1, LANG_STR("IDS_CHN_AUDIENCE"));
	m_ctrRole.SetCurSel(0);
	m_ctrRole.ShowWindow(SW_HIDE);
   
	m_edtCdnNumber.MoveWindow((ClientRect.Width() / 2 - 120) , 127, 240 , 22 , TRUE);
	m_chkSelfDefineVideoProfile.MoveWindow(80 , 170, 140 , 22 , TRUE);

	//自定义分辨率
	m_edtResolutionWidth.SetFont(&m_ftDesc);
	int left = 70;
	m_edtResolutionWidth.MoveWindow(left , 225 , 70 , 20 , TRUE);
	m_edtResolutionWidth.ShowCaret();
	m_edtResolutionWidth.SetTip(_T("width"));
	m_edtResolutionHeight.SetFont(&m_ftDesc);
	m_edtResolutionHeight.ShowCaret();
	left += 90;
	m_edtResolutionHeight.MoveWindow(left , 225 , 70, 20, TRUE);
	m_edtResolutionHeight.SetTip(_T("height"));
	m_edtVideoFPS.SetFont(&m_ftDesc);
	m_edtVideoFPS.ShowCaret();
	left += 90;
	m_edtVideoFPS.MoveWindow(left, 225 , 70 , 20 , TRUE);
	m_edtVideoFPS.SetTip(_T("fps"));
	m_edtVideoBitrate.SetFont(&m_ftDesc);
	left += 90;
	m_edtVideoBitrate.MoveWindow(left, 225 , 70 , 20, TRUE);
	m_edtVideoBitrate.ShowCaret();
	m_edtVideoBitrate.SetTip(_T("bitrate"));

	int height = 36  ;
	m_btnJoin.MoveWindow(ClientRect.Width() / 2 - 180 , 310, 350, height, TRUE);
	m_btnTest.MoveWindow(ClientRect.Width() / 2 - 180 , 355 , 108, height, TRUE);
	m_btnSetup.MoveWindow(ClientRect.Width() / 2 - 60 , 355 , 240, height, TRUE);
	//m_btnRTMP.MoveWindow(ClientRect.Width() / 2 - 180 * n / (float)d, 401 * n / (float)d, 108 * n / (float)d, height, TRUE);//m_btnTest downside
	m_btnRTMP.ShowWindow(SW_HIDE);//

	m_btnJoin.SetBackColor(RGB(0x00, 0xA0, 0xE9), RGB(0x05, 0x78, 0xAA), RGB(0x05, 0x78, 0xAA), RGB(0xE6, 0xE6, 0xE6));
	m_btnJoin.SetFont(&m_ftBtn);
	m_btnJoin.SetTextColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xCC, 0xCC, 0xCC));
	m_btnJoin.SetWindowText(LANG_STR("IDS_CHN_BTJOIN"));

	m_btnTest.SetBorderColor(RGB(0xD8, 0xD8, 0xD8), RGB(0x00, 0xA0, 0xE9), RGB(0x00, 0xA0, 0xE9), RGB(0xCC, 0xCC, 0xCC));
	m_btnTest.SetBackColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_btnTest.SetFont(&m_ftBtn);
	m_btnTest.SetTextColor(RGB(0x55, 0x58, 0x5A), RGB(0x00, 0xA0, 0xE9), RGB(0x00, 0xA0, 0xE9), RGB(0xCC, 0xCC, 0xCC));
	m_btnTest.SetWindowText(LANG_STR("IDS_CHN_BTTEST"));

	m_btnRTMP.SetBorderColor(RGB(0xD8, 0xD8, 0xD8), RGB(0x00, 0xA0, 0xE9), RGB(0x00, 0xA0, 0xE9), RGB(0xCC, 0xCC, 0xCC));
	m_btnRTMP.SetBackColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_btnRTMP.SetFont(&m_ftBtn);
	m_btnRTMP.SetTextColor(RGB(0x55, 0x58, 0x5A), RGB(0x00, 0xA0, 0xE9), RGB(0x00, 0xA0, 0xE9), RGB(0xCC, 0xCC, 0xCC));

	m_btnSetup.SetBorderColor(RGB(0xD8, 0xD8, 0xD8), RGB(0x00, 0xA0, 0xE9), RGB(0x00, 0xA0, 0xE9), RGB(0xCC, 0xCC, 0xCC));
	m_btnSetup.SetBackColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_btnSetup.SetFont(&m_ftBtn);
	m_btnSetup.SetTextColor(RGB(0x55, 0x58, 0x5A), RGB(0x00, 0xA0, 0xE9), RGB(0x00, 0xA0, 0xE9), RGB(0xCC, 0xCC, 0xCC));
	m_btnSetup.SetWindowText(_T("1920*1080,15fps, 3mbps"));

	m_ctrPassword.SetFocus();
	m_edtCdnNumber.SetFocus();
	m_edtResolutionWidth.SetFocus();
	m_edtResolutionHeight.SetFocus();
	m_edtVideoBitrate.SetFocus();
	m_edtVideoFPS.SetFocus();
	CMFCButton::EnableWindowsTheming(FALSE);
}

void CEnterChannelDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	DrawClient(&dc);
}

void CEnterChannelDlg::DrawClient(CDC *lpDC)
{
	CRect	rcText;
	CRect	rcClient;
	LPCTSTR lpString = NULL;

	GetClientRect(&rcClient);

	
    CFont* defFont = lpDC->SelectObject(&m_ftDesc);
	lpDC->SetBkColor(RGB(0xFF, 0xFF, 0xFF));
	lpDC->SetTextColor(RGB(0x44, 0x45, 0x46));

	lpDC->SelectObject(&m_penFrame);
	rcText.SetRect(rcClient.Width() / 2 - 180, 25 , rcClient.Width() / 2 + 170, 57);
	lpDC->RoundRect(&rcText, CPoint(32 , 32 ));

	rcText.OffsetRect(0, 48) ;
	lpDC->RoundRect(&rcText, CPoint(32, 32));

	lpString = LANG_STR("IDS_CHN_ROLETITLE");
	lpDC->SetTextColor(RGB(0xD8, 0xD8, 0xD8));
	//lpDC->TextOut(220, 80, lpString, _tcslen(lpString));

	rcText.OffsetRect(0, 48);
	lpDC->RoundRect(&rcText, CPoint(32, 32));
	
	if (m_chkSelfDefineVideoProfile.GetCheck()){

		rcText.OffsetRect(0, 96 );
		rcText.right = rcText.left + 80;
		lpDC->RoundRect(&rcText, CPoint(32 , 32));

		rcText.OffsetRect(90 , 0);
		rcText.right = rcText.left + 80;
		lpDC->RoundRect(&rcText, CPoint(32 , 32 ));

		rcText.OffsetRect(90 , 0);
		rcText.right = rcText.left + 80;
		lpDC->RoundRect(&rcText, CPoint(32, 32));

		rcText.OffsetRect(90 , 0);
		rcText.right = rcText.left + 80 ;
		lpDC->RoundRect(&rcText, CPoint(32, 32));
	}

	lpDC->SelectObject(defFont);

	// Done with the font.  Delete the font object.
	//	font.DeleteObject();
}

void CEnterChannelDlg::OnBnClickedBtntestChannel()
{
	
	m_dlgDevice.ShowWindow(SW_SHOW);
	m_dlgDevice.CenterWindow();
}


void CEnterChannelDlg::OnBnClickedBtnjoinChannel()
{
	
	CString     strKey;
    CString     strChannelName;
    CString     strInfo;
    CString     strOperation;
    BOOL        bFound = FALSE;
    BOOL        bSuccess = FALSE;

    m_ctrChannel.GetWindowText(strChannelName);
    m_ctrPassword.GetWindowText(strKey);

	GetParent()->SendMessage(WM_JOINCHANNEL, 0, 0);
}


void CEnterChannelDlg::OnBnClickedBtnsetChannel()
{
	

	GetParent()->SendMessage(WM_GONEXT, 0, 0);
}

void CEnterChannelDlg::OnCbnSelchangeCmbRole()
{
	int nSel = m_ctrRole.GetCurSel();

	if (nSel == 0)
		CAgoraObject::GetAgoraObject()->SetClientRole(CLIENT_ROLE_BROADCASTER);
	else
		CAgoraObject::GetAgoraObject()->SetClientRole(CLIENT_ROLE_AUDIENCE);
}

CString CEnterChannelDlg::GetChannelName()
{
	CString strChannelName;

	m_ctrChannel.GetWindowText(strChannelName);

	return strChannelName;
}

CString CEnterChannelDlg::GetCdnRtmp()
{
	CString strCdn = _T("");
	m_edtCdnNumber.GetWindowText(strCdn);
	if (strCdn.Compare(LANG_STR("IDS_CHN_CDNNUMBER")) == 0
		|| strCdn.IsEmpty()){
		CString strChannelName;

		m_ctrChannel.GetWindowText(strChannelName);
		strCdn = strChannelName;
	}

	CString baseRtmp = _T("rtmp://vid-218.push.chinanetcenter.broadcastapp.agora.io/live/");
	return baseRtmp + strCdn;
}

void CEnterChannelDlg::SetVideoString(LPCTSTR lpVideoString)
{
	m_btnSetup.SetWindowText(lpVideoString);
}

void CEnterChannelDlg::OnBnClickedBtnRtmp()
{
	GetParent()->SendMessage(WM_SETPUBLISH_RTMP, 0, 0);
}

void CEnterChannelDlg::OnBnClickedCheckSelfVideoprofile()
{
	if (m_chkSelfDefineVideoProfile.GetCheck()){
		bSelfDefineVideoProfile = true;
		Invalidate();
		ShowSelfEdit(true);
		m_btnSetup.EnableWindow(TRUE);
	}
	else{
		bSelfDefineVideoProfile = false;
		Invalidate();
		ShowSelfEdit(false);
		//ClearSelftEdit();
		m_btnSetup.EnableWindow(FALSE);
	}
}

void CEnterChannelDlg::ShowSelfEdit(bool bShow)
{
	int mode = bShow ? SW_SHOW : SW_HIDE;
	m_edtResolutionHeight.ShowWindow(mode);
	m_edtResolutionWidth.ShowWindow(mode);
	m_edtVideoBitrate.ShowWindow(mode);
	m_edtVideoFPS.ShowWindow(mode);
}

void CEnterChannelDlg::ClearSelftEdit()
{
	m_edtResolutionHeight.SetWindowText(_T(""));
	m_edtResolutionWidth.SetWindowText(_T(""));
	m_edtVideoBitrate.SetWindowText(_T(""));
	m_edtVideoFPS.SetWindowText(_T(""));
}

void CEnterChannelDlg::InitSelfEdit()
{
	m_edtResolutionHeight.SetWindowText(_T("640"));
	m_edtResolutionWidth.SetWindowText(_T("480"));
	m_edtVideoBitrate.SetWindowText(_T("15"));
	m_edtVideoFPS.SetWindowText(_T("500"));
}
void CEnterChannelDlg::GetSelfDefine(int& width, int height, int fps, int bitrate)
{
	CString strWidth, strHeight, strfps, strBitrate;
	m_edtResolutionWidth.GetWindowText(strWidth);
	m_edtResolutionHeight.GetWindowText(strHeight);
	m_edtVideoFPS.GetWindowText(strfps);
	m_edtVideoBitrate.GetWindowText(strBitrate);

	if (strWidth.Compare(_T("width"))==0 || strWidth.IsEmpty()){
		width = 640;
	}
	else{
		width = _ttoi(strWidth.GetBuffer(0));
	}

	if (strHeight.Compare(_T("height")) ==0|| strHeight.IsEmpty()){
		height = 480;
	}
	else{
		height = _ttoi(strHeight.GetBuffer(0));
	}

	if (strfps.Compare(_T("fps")) ==0|| strfps.IsEmpty()){
		fps = 15;
	}
	else{
		fps = _ttoi(strfps.GetBuffer(0));
	}

	if (strBitrate.Compare(_T("bitrate"))==0 || strBitrate.IsEmpty()){
		bitrate = 500;
	}
	else{
		bitrate = _ttoi(strBitrate.GetBuffer(0));
	}
}


void CEnterChannelDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}

void CEnterChannelDlg::SetCtrlPos()
{
	CRect ClientRect;

	GetClientRect(&ClientRect);
	int top = 33;
	m_ctrChannel.MoveWindow(ClientRect.Width() / 2 - 150, top, 300, 22, TRUE);
	top += 49;
	m_ctrPassword.MoveWindow(ClientRect.Width() / 2 - 150, top, 120, 22, TRUE);//82
	m_ctrRole.MoveWindow(ClientRect.Width() / 2 + 40, top - 4, 130, 22, TRUE);
	top += 45;
	m_edtCdnNumber.MoveWindow((ClientRect.Width() / 2 - 120), top, 240, 22, TRUE);//127
	top += 49;
	m_chkSelfDefineVideoProfile.MoveWindow(80, top, 140, 22, TRUE);//176

	//自定义分辨率
	m_edtResolutionWidth.SetFont(&m_ftDesc);
	int left = 75;
	top += 49;
	m_edtResolutionWidth.MoveWindow(left, top, 70, 20, TRUE);//225
	left += 90;
	m_edtResolutionHeight.MoveWindow(left, top, 70, 20, TRUE);
	left += 90;
	m_edtVideoFPS.MoveWindow(left, top, 70, 20, TRUE);
	left += 90;
	m_edtVideoBitrate.MoveWindow(left, top, 70, 20, TRUE);

	int height = 36;
	m_btnJoin.MoveWindow(ClientRect.Width() / 2 - 180, 310, 350, height, TRUE);
	m_btnTest.MoveWindow(ClientRect.Width() / 2 - 180, 355, 108, height, TRUE);
	m_btnSetup.MoveWindow(ClientRect.Width() / 2 - 60, 355, 240, height, TRUE);
	//m_btnRTMP.MoveWindow(ClientRect.Width() / 2 - 180 * n / (float)d, 401 * n / (float)d, 108 * n / (float)d, height, TRUE);//m_btnTest downside
}