// SetupDlg.cpp : implement file
//

#include "stdafx.h"
#include "OpenLive.h"
#include "SetupDlg.h"
#include "afxdialogex.h"


// CSetupDlg Dialog

IMPLEMENT_DYNAMIC(CSetupDlg, CDialogEx)

CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupDlg::IDD, pParent)
{

}

CSetupDlg::~CSetupDlg()
{
}

void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTNCANCEL_SETUP, m_btnCancel);
	DDX_Control(pDX, IDC_BTNCONFIRM_SETUP, m_btnConfirm);
	DDX_Control(pDX, IDC_CKSAVESETTING_SETUP, m_ckSaveSettings);
	DDX_Control(pDX, IDC_CKSWPWH_SETUP, m_ckSwapWH);
	DDX_Control(pDX, IDC_CKFULLBAND_SETUP, m_ckFullBand);
	DDX_Control(pDX, IDC_CKSTEREO_SETUP, m_ckStereo);
	DDX_Control(pDX, IDC_CKFULLBITRATE_SETUP, m_ckFullBitrate);
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTNCONFIRM_SETUP, &CSetupDlg::OnBnClickedBtnconfirmSetup)
//	ON_CBN_SELCHANGE(IDC_CMBRES_SETUP, &CSetupDlg::OnCbnSelchangeCmbresSetup)
//	ON_CBN_SELCHANGE(IDC_CMBCODEC_SETUP, &CSetupDlg::OnCbnSelchangeCmbresSetup)

	ON_WM_HSCROLL()
	ON_WM_LBUTTONDBLCLK()

	ON_BN_CLICKED(IDC_BUTTON1, &CSetupDlg::OnBnClickedBtncancelSetup)
END_MESSAGE_MAP()


// CSetupDlg Message Handler


BOOL CSetupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ftHead.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	m_ftDes.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	m_ftBtn.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	m_penFrame.CreatePen(PS_SOLID, 1, RGB(0xD8, 0xD8, 0xD8));
	m_cbxVideoProfile.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, CRect(0, 0, 300, 40), this, IDC_CMBVDOPRF_SETUP);
	SetBackgroundColor(RGB(0xFF, 0xFF, 0xFF), TRUE);
    InitData();
    InitCtrls();

	if (m_agConfig.IsAutoSaveEnabled())
		m_ckSaveSettings.SetCheck(TRUE);
	else
		m_ckSaveSettings.SetCheck(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CSetupDlg::InitCtrls()
{
	CRect ClientRect;

	MoveWindow(0, 0, 320, 450, 1);
	GetClientRect(&ClientRect);

	int nResolutionIndex = 0;
	CString str;
	
	m_cbxVideoProfile.MoveWindow(210, 80, 200, 22, TRUE);
	m_cbxVideoProfile.SetFont(&m_ftDes);
	m_cbxVideoProfile.SetButtonImage(IDB_CMBBTN, 12, 12, RGB(0xFF, 0x00, 0xFF));
	m_cbxVideoProfile.SetFaceColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_cbxVideoProfile.SetListMaxHeight(600);

	m_ckSwapWH.MoveWindow(80, 120, 20, 20, TRUE);
	m_ckSaveSettings.MoveWindow(80, ClientRect.Height() - 95, 20, 20, TRUE);

	m_ckFullBand.MoveWindow(80, 220, 20, 20, TRUE);
	m_ckStereo.MoveWindow(80, 240, 20, 20, TRUE);
	m_ckFullBitrate.MoveWindow(80, 260, 20, 20, TRUE);

	m_btnCancel.MoveWindow(ClientRect.Width() / 2 - 93, ClientRect.Height() - 58, 174, 36, TRUE);

	m_btnConfirm.MoveWindow(ClientRect.Width() / 2 + 93, ClientRect.Height() - 58, 174, 36, TRUE);

	for (int nIndex = 0; nIndex < 31; nIndex++) {
		m_cbxVideoProfile.InsertString(nIndex, m_szProfileDes[nIndex]);
		m_cbxVideoProfile.SetItemData(nIndex, (DWORD_PTR)m_nProfileValue[nIndex]);
	}

	m_btnCancel.SetBorderColor(RGB(0xD8, 0xD8, 0xD8), RGB(0x00, 0xA0, 0xE9), RGB(0x00, 0xA0, 0xE9), RGB(0xCC, 0xCC, 0xCC));
	m_btnCancel.SetBackColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_btnCancel.SetTextColor(RGB(0x55, 0x58, 0x5A), RGB(0x00, 0xA0, 0xE9), RGB(0x00, 0xA0, 0xE9), RGB(0xCC, 0xCC, 0xCC));

	m_btnConfirm.SetBackColor(RGB(0, 160, 239), RGB(0, 160, 239), RGB(0, 160, 239), RGB(192, 192, 192));
	m_btnConfirm.SetFont(&m_ftBtn);
	m_btnConfirm.SetTextColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xC8, 0x64), RGB(0xFF, 0xC8, 0x64), RGB(0xCC, 0xCC, 0xCC));
	m_btnConfirm.SetWindowText(LANG_STR("IDS_SET_BTCONFIRM"));

    if (m_agConfig.IsAutoSaveEnabled())
        nResolutionIndex = m_agConfig.GetSolution();
    else
        nResolutionIndex = 15;
    
    m_cbxVideoProfile.SetCurSel(nResolutionIndex);
}

void CSetupDlg::InitData()
{
	int i = 0, j = 0;
	m_szProfileDes[j] = _T("160x120 15fps");//65kbps
	m_nProfileValue[j] = 0;
	VideoProfile profile;
	profile.width = 160;
	profile.height = 120;
	profile.fps = 15;
	profile.bitrate = 65;
	
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;

	m_szProfileDes[j] = _T("120x120 15fps");//50kbps
	m_nProfileValue[j] = 2;
	profile.width = 120;
	profile.height = 120;
	profile.fps = 15;
	profile.bitrate = 50;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;


	m_szProfileDes[j] = _T("320x180 15fps");//140kbps
	m_nProfileValue[j] = 10;
	profile.width = 320;
	profile.height = 180;
	profile.fps = 15;
	profile.bitrate = 140;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;

	m_szProfileDes[j] = _T("180x180 15fps");//100kbps
	m_nProfileValue[j] = 12;
	profile.width = 180;
	profile.height = 180;
	profile.fps = 15;
	profile.bitrate = 100;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;
	m_szProfileDes[j] = _T("240x180 15fps");//120kbps
	m_nProfileValue[j] = 13;
	profile.width = 240;
	profile.height = 180;
	profile.fps = 15;
	profile.bitrate = 120;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;


	m_szProfileDes[j] = _T("320x240 15fps");//200kbps
	m_nProfileValue[j] = 20;
	profile.width = 320;
	profile.height = 240;
	profile.fps = 15;
	profile.bitrate = 200;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;
	m_szProfileDes[j] = _T("240x240 15fps");//140kbps
	m_nProfileValue[j] = 22;
	profile.width = 240;
	profile.height = 240;
	profile.fps = 15;
	profile.bitrate = 140;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;
	m_szProfileDes[j] = _T("424x240 15fps");//220kbps
	m_nProfileValue[j] = 23;
	profile.width = 424;
	profile.height = 240;
	profile.fps = 15;
	profile.bitrate = 220;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;


	m_szProfileDes[j] = _T("640x360 15fps");//400kbps
	m_nProfileValue[j] = 30;
	profile.width = 640;
	profile.height = 360;
	profile.fps = 15;
	profile.bitrate = 400;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;
	m_szProfileDes[j] = _T("360x360 15fps");//260kbps
	m_nProfileValue[j] = 32;
	profile.width = 360;
	profile.height = 360;
	profile.fps = 15;
	profile.bitrate = 260;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;
	m_szProfileDes[j] = _T("640x360 30fps");//600kbps
	m_nProfileValue[j] = 33;
	profile.width = 640;
	profile.height = 360;
	profile.fps = 30;
	profile.bitrate = 600;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;
	m_szProfileDes[j] = _T("360x360 30fps");//400kbps
	m_nProfileValue[j] = 35;
	profile.width = 360;
	profile.height = 360;
	profile.fps = 30;
	profile.bitrate = 400;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;
	m_szProfileDes[j] = _T("480x360 15fps");//320kbps
	m_nProfileValue[j] = 36;
	profile.width = 480;
	profile.height = 360;
	profile.fps = 15;
	profile.bitrate = 320;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;
	m_szProfileDes[j] = _T("480x360 30fps");//490kbps
	m_nProfileValue[j] = 37;
	profile.width = 480;
	profile.height = 360;
	profile.fps = 30;
	profile.bitrate = 490;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;
	m_szProfileDes[j] = _T("640x360 15fps");//800kbps
	m_nProfileValue[j] = 38;
	profile.width = 640;
	profile.height = 360;
	profile.fps = 15;
	profile.bitrate = 800;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;


	m_szProfileDes[j] = _T("640x480 15fps");//500kbps
	m_nProfileValue[j] = 40;
	profile.width = 640;
	profile.height = 480;
	profile.fps = 15;
	profile.bitrate = 500;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;
	m_szProfileDes[j] = _T("480x480 15fps");//400kbps
	m_nProfileValue[j] = 42;
	profile.width = 480;
	profile.height = 480;
	profile.fps = 15;
	profile.bitrate = 400;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;

	m_szProfileDes[j] = _T("640x480 30fps");//750kbps
	m_nProfileValue[j] = 43;
	profile.width = 640;
	profile.height = 480;
	profile.fps = 30;
	profile.bitrate = 750;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;
	m_szProfileDes[j] = _T("480x480 30fps");//600kbps
	m_nProfileValue[j] = 44;
	profile.width = 480;
	profile.height = 480;
	profile.fps = 30;
	profile.bitrate = 600;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;
	m_szProfileDes[j] = _T("848x480 15fps");//610kbps
	m_nProfileValue[j] = 47;
	profile.width = 848;
	profile.height = 480;
	profile.fps = 15;
	profile.bitrate = 610;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;
	m_szProfileDes[j] = _T("848x480 30fps"); //930kbps
	m_nProfileValue[j] = 48;
	profile.width = 848;
	profile.height = 480;
	profile.fps = 30;
	profile.bitrate = 930;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;


	m_szProfileDes[j] = _T("1280x720 15fps"); //1130kbps
	m_nProfileValue[j] = 50;
	profile.width = 1280;
	profile.height = 720;
	profile.fps = 15;
	profile.bitrate = 1130;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;

	m_szProfileDes[j] = _T("1280x720 30fps"); //1710kbps
	m_nProfileValue[j] = 52;
	profile.width = 1280;
	profile.height = 720;
	profile.fps = 30;
	profile.bitrate = 1710;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;
	m_szProfileDes[j] = _T("960x720 15fps"); //910kbps
	m_nProfileValue[j] = 54;
	profile.width = 960;
	profile.height = 720;
	profile.fps = 15;
	profile.bitrate = 910;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;
	m_szProfileDes[j] = _T("960x720 30fps"); //1380kbps
	m_nProfileValue[j] = 55;
	profile.width = 960;
	profile.height = 720;
	profile.fps = 30;
	profile.bitrate = 1380;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;


	m_szProfileDes[j] = _T("1920x1080 15fps"); //2080kbps
	m_nProfileValue[j] = 60;
	profile.width = 1920;
	profile.height = 1080;
	profile.fps = 15;
	profile.bitrate = 2080;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;

	m_szProfileDes[j] = _T("1920x1080 30fps"); //3150kbps
	m_nProfileValue[j] = 62;
	profile.width = 1920;
	profile.height = 1080;
	profile.fps = 30;
	profile.bitrate = 3150;
	m_mapVideoProfile[(VIDEO_PROFILE_TYPE)m_nProfileValue[j++]] = profile;

	//m_szProfileDes[27] = _T("1920x1080 60fps"); //4780kbps
	//m_nProfileValue[27] = 64;
	//m_szProfileDes[28] = _T("2560x1440 30fps"); //4850kbps
	//m_nProfileValue[28] = 66;
	//m_szProfileDes[29] = _T("3560x1440 60fps"); //7350kbps
	//m_nProfileValue[29] = 67;

	//m_szProfileDes[30] = _T("3840x2160 30fps"); //8190kbps
	//m_nProfileValue[30] = 70;
	//m_szProfileDes[31] = _T("3840x2160 60fps"); //13500kbps
	//m_nProfileValue[31] = 72;
}

void CSetupDlg::DrawClient(CDC *lpDC)
{
	CRect	rcText;
	CRect	rcClient;
	LPCTSTR lpString = NULL;

	GetClientRect(&rcClient);

	CFont *lpDefFont = lpDC->SelectObject(&m_ftHead);
	CPen  *lpDefPen = lpDC->SelectObject(&m_penFrame);

	rcText.SetRect(rcClient.Width() / 2 - 188, 75, rcClient.Width() / 2 + 172, 107);
	lpDC->RoundRect(&rcText, CPoint(32, 32));

	lpDC->SetBkColor(RGB(0xFF, 0xFF, 0xFF));
	lpDC->SetTextColor(RGB(0xD8, 0xD8, 0xD8));

	lpDC->SetTextColor(RGB(0x44, 0x45, 0x46));
	lpString = LANG_STR("IDS_SET_RESOLUTION");
	lpDC->TextOut(80, 83, lpString, _tcslen(lpString));
	
	lpString = LANG_STR("IDS_SET_SWAPWH");
	lpDC->TextOut(100, 120, lpString, _tcslen(lpString));

	lpString = LANG_STR("IDS_SET_FULLBAND");
	lpDC->TextOut(100, 220, lpString, _tcslen(lpString));
	lpString = LANG_STR("IDS_SET_STEREO");
	lpDC->TextOut(100, 240, lpString, _tcslen(lpString));
	lpString = LANG_STR("IDS_SET_FULLBITRATE");
	lpDC->TextOut(100, 260, lpString, _tcslen(lpString));


	lpString = LANG_STR("IDS_SET_SAVESETTING");
	lpDC->TextOut(100, rcClient.Height() - 95, lpString, _tcslen(lpString));

	lpDC->SelectObject(lpDefPen);
	lpDC->SelectObject(lpDefFont);
}

void CSetupDlg::OnBnClickedBtnconfirmSetup()
{
	
	GetParent()->SendMessage(WM_GOBACK, 0, 0);

	if (m_ckSaveSettings.GetCheck() == TRUE) {
		m_agConfig.EnableAutoSave(TRUE);
        m_agConfig.SetSolution(m_cbxVideoProfile.GetCurSel());
	}
	else
		m_agConfig.EnableAutoSave(FALSE);

	BOOL bFullBand = m_ckFullBand.GetCheck();
	BOOL bStereo = m_ckStereo.GetCheck();
	BOOL bFullBitrate = m_ckFullBitrate.GetCheck();

//	CAgoraObject::GetAgoraObject()->SetHighQualityAudio(bFullBand, bStereo, bFullBitrate);
}

void CSetupDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	DrawClient(&dc);
}

int CSetupDlg::GetVideoSolution()
{
    int nIndex = m_cbxVideoProfile.GetCurSel();
    return (int)m_cbxVideoProfile.GetItemData(nIndex);
}

void CSetupDlg::SetVideoSolution(int nIndex)
{
	m_cbxVideoProfile.SetCurSel(nIndex);
}

CString CSetupDlg::GetVideoSolutionDes()
{
    int nIndex = m_cbxVideoProfile.GetCurSel();
    if (nIndex == -1)
        nIndex = 0;

    return (CString)m_szProfileDes[nIndex];
}

void CSetupDlg::SetWHSwap(BOOL bSwap)
{
	m_ckSwapWH.SetCheck(bSwap);
}

BOOL CSetupDlg::IsWHSwap()
{
	return (BOOL)m_ckSwapWH.GetCheck();
}

void CSetupDlg::OnBnClickedBtncancelSetup()
{	
	GetParent()->SendMessage(WM_GOBACK, 0, 0);
}
