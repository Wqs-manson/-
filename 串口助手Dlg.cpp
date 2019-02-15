// 串口助手Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "串口助手.h"
#include "串口助手Dlg.h"
#include"winsock.h"
#include"mysql.h"
#pragma comment(lib,"libmySQL.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//自定义变量
int flag=1,port=0;
CString RX,RX_Buff;
LONG RX_temp=0;
MYSQL mysql;
MYSQL_RES *res;
MYSQL_ROW row;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	m_edit1 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//颜色控制
	m_colorEditText = RGB(0,0,0);
	m_colorEditBK = RGB(255,255,255);
	m_pEditBkBrush = new CBrush(RGB(255,255,255));
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Control(pDX, IDC_COMBO5, m_combo5_5);
	DDX_Control(pDX, IDC_COMBO4, m_combo4_4);
	DDX_Control(pDX, IDC_COMBO3, m_combo3_3);
	DDX_Control(pDX, IDC_COMBO2, m_combo2_2);
	DDX_Control(pDX, IDC_COMBO1, m_combo1_1);
	DDX_Control(pDX, IDC_EDIT1, m_edit1_1);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscomm);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_CBIndex(pDX, IDC_COMBO1, m_combo1);
	DDX_CBIndex(pDX, IDC_COMBO2, m_combo2);
	DDX_CBIndex(pDX, IDC_COMBO3, m_combo3);
	DDX_CBIndex(pDX, IDC_COMBO4, m_combo4);
	DDX_CBIndex(pDX, IDC_COMBO5, m_combo5);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, FALSE);			// Set big icon   TRUE
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//设置combo初始值
	m_combo1=2;
	m_combo2=3;
	m_combo3=0;
	m_combo4=0;
	m_combo5=0;
	//字体部分
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT1);
    CFont *pFont=new CFont;
    pFont->CreatePointFont(110,_T("楷体"),NULL);//_GB2312
    pEdit->SetFont(pFont,TRUE);
	//默认文本框内容
	UpdateData(FALSE);  //更新编辑框内容
	GetDlgItem(IDC_STATIC_LED)->ShowWindow(SW_HIDE);//指示灯
	//添加状态栏
	CTime time;
    time=CTime::GetCurrentTime();
	UINT array[5];
	for(int i=0;i<5;i++)
	{
		array[i] = 350+i;
	}
	m_StatusBar.Create(this); //创建状态栏窗口
	m_StatusBar.SetIndicators(array,sizeof(array)/sizeof(UINT)); //添加面板
	m_StatusBar.SetPaneInfo(0,array[0],0,137); //设置面板宽度
	m_StatusBar.SetPaneInfo(1,array[1],0,70); //设置面板宽度
	m_StatusBar.SetPaneInfo(2,array[2],0,115); //设置面板宽度
	m_StatusBar.SetPaneInfo(3,array[3],0,155); //设置面板宽度
	m_StatusBar.SetPaneInfo(4,array[4],0,127); //设置面板宽度
	//设置面板文本
	m_StatusBar.SetPaneText(0,"设置：");//COM3,9600,N,8,1
	m_StatusBar.SetPaneText(1,"状态：未连接");
//	m_StatusBar.SetPaneText(2,"接收：0");
	m_StatusBar.SetPaneText(3,"当前时间：");
	m_StatusBar.SetPaneText(4,time.Format("%Y-%m-%d-%X"));
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0); //显示状态栏
	RECT m_rect;
	m_StatusBar.GetItemRect(3,&m_rect); //获取第四个面板的区域
	//设置定时器
	SetTimer(1,1000,NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CMyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CMyDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CMyDlg)
	ON_EVENT(CMyDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

MYSQL_RES* mysql_conn_sqlQuery(MYSQL *mysql,char *sql_Query)
{
    if(mysql_query(mysql,sql_Query))
    {
        printf("MySQL quer error:%s\n",mysql_error(mysql));
        exit(1);
    }
    return mysql_use_result(mysql);
}
void CMyDlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	CTime time;
    time=CTime::GetCurrentTime();
	VARIANT data;
	COleSafeArray data2;
	CByteArray datatemp;
    CString strtemp,buffer;
	LONG len,i;
	BYTE Inbyte[2048],temp;
	UpdateData(TRUE);  //读编辑框内容
	char s2[100];
    char s3[9];
	if(m_mscomm.GetCommEvent()==2) //事件值为2表示接收缓冲区内有字符
	{
		data=m_mscomm.GetInput();  //读缓冲区
		data2=data;  //VARIANT型变量转换为ColeSafeArray型变量
        len=data2.GetOneDimSize();  ////得到有效数据长度
		RX_temp=RX_temp+len;
		RX.Format("%d",RX_temp);
		RX_Buff="接收：";
		RX_Buff+=RX;
		m_StatusBar.SetPaneText(3,RX_Buff);	
		for(i=0;i<len;i++)
		data2.GetElement(&i,Inbyte+i);//转换为BYTE型数组
		for(i=0;i<len;i++)             //将数组转换为Cstring型变量
		{
			temp=*(char*)(Inbyte+i);  //将字符送入临时变量strtemp存放
			s2[i]=temp;
			strtemp.MakeUpper();
			strtemp.Insert(2," ");
			 strtemp.Format("%c",temp);    //将字符送入临时变量strtemp存放
			buffer+=strtemp;  //将字符串送入临时变量buffer中存放
		}
		s2[i]='\0';	
	m_edit1=m_edit1+buffer+"";//将字符串写入文本框
	}
	/////////////////////////////////////////  截取卡片类型 type
	 char s1[5];
	 for(int n=0;n<=2;n++)
	 {
		s1[n]=s2[n];
	 }
	 s1[3]='\0';

	CString str1;
	str1.Format(s1);
	//////////////////////////////////////////截取卡片ID
		 
	 for(int m=0;m<i-2;m++)
	 {
		s3[m]=s2[3+m];
	 }
	 s3[m]='\0';
	
	CString str2,str3;
	str2.Format(s3);
str3.Format(s2);
	char sql_query[100];
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql,"39.105.105.165","root","root","card",3306,NULL,0))
    {
      // AfxMessageBox("连接成功！");
    }
    else
    {
       // AfxMessageBox("连接失败");
    }	
	memset(sql_query,'\0',100);
 sprintf(sql_query,"INSERT INTO card (id) VALUES ('"+str3+"')");
    res=mysql_conn_sqlQuery(&mysql,sql_query);
	mysql_free_result(res);
	UpdateData(FALSE);  //更新编辑框内容
	m_edit1_1.LineScroll(m_edit1_1.GetLineCount());//设置编辑框滚动条在最后
}

void CMyDlg::OnButton1() //连接按钮
{
	// TODO: Add your control notification handler code here
	int myCom;
	int	mybaud,mypar,mynum,mystop;//串口号码
	CString	myParity,number,stoptemp; //奇偶校验类型
	CString	myBaudRate;//通信波特率
	CString strPara,strStatus,strtemp; 
	CString trs=_T("123456789");
	if(flag==1)
	{
		myCom=m_combo1_1.GetCurSel()+1;
		m_mscomm.SetCommPort(myCom);
		mybaud=m_combo2_2.GetCurSel();
		switch(mybaud)
		{
		case 0:
			{
			myBaudRate="1200";break;
			}
		case 1:
			{
			myBaudRate="2400";break;
			}
		case 2:
			{
			myBaudRate="4800";break;
			}
		case 3:
			{
			myBaudRate="9600";break;
			}
		case 4:
			{
			myBaudRate="14400";break;
			}
		case 5:
			{
			myBaudRate="19200";break;
			}
		case 6:
			{
			myBaudRate="28800";break;
			}
		case 7:
			{
			myBaudRate="38400";break;
			}
		case 8:
			{
			myBaudRate="57600";break;
			}
		case 9:
			{
			myBaudRate="115200";break;
			}
		case 10:
			{
			myBaudRate="128000";break;
			}
		case 11:
			{
			myBaudRate="256000";break;
			}
		case 12:
			{
			myBaudRate="460800";break;
			}
		case 13:
			{
			myBaudRate="614400";break;
			}
		case 14:
			{
			myBaudRate="921600";break;
			}
		case 15:
			{
			myBaudRate="1228800";break;
			}
		case 16:
			{
			myBaudRate="1382400";break;
			}
		}

		mypar=m_combo3_3.GetCurSel();
		switch(mypar)
		{
		case 0:
			{
			myParity="N";break;
			}
		case 1:
			{
			myParity="E";break;
			}
		case 2:
			{
			myParity="O";break;
			}
		}

		mynum=m_combo4_4.GetCurSel();
		switch(mynum)
		{
		case 0:
			{
			number="8";break;
			}
		case 1:
			{
			number="7";break;
			}
		case 2:
			{
			number="6";break;
			}
		}
		mystop=m_combo5_5.GetCurSel();
		switch(mynum)
		{
		case 0:
			{
			stoptemp="1";break;
			}
		case 1:
			{
			stoptemp="2";break;
			}
		}

		strPara=myBaudRate;
		strPara+=",";
		strPara+=myParity;
		strPara+=",";
		strPara+=number;
		strPara+=",";
		strPara+=stoptemp;
		m_mscomm.SetSettings(strPara);
		strtemp=trs[myCom-1];//
		m_StatusBar.SetPaneText(0,"设置：COM"+strtemp+","+strPara);
		m_StatusBar.SetPaneText(1,"状态：已连接");
		m_mscomm.SetInputMode(1); //输入方式为二进制方式
		m_mscomm.SetRThreshold(1); //参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
		m_mscomm.SetPortOpen(TRUE);//打开串口
		//MessageBox("连接成功！");
		port=1;
		GetDlgItem(IDC_STATIC_LED)->ShowWindow(TRUE);
		SetDlgItemText(IDC_BUTTON1,"关闭");
		flag=0;
	}
	else
	{
		m_mscomm.SetPortOpen(0);
		AfxMessageBox("串口关闭成功！");
		port=0;
		m_StatusBar.SetPaneText(0,"设置：");
		m_StatusBar.SetPaneText(1,"状态：未连接");
		GetDlgItem(IDC_STATIC_LED)->ShowWindow(SW_HIDE);
		SetDlgItemText(IDC_BUTTON1,"连接");
		flag=1;
	}
}
void CMyDlg::OnButton2() //清空接收
{
	// TODO: Add your control notification handler code here
	m_edit1.Empty(); 
	UpdateData(FALSE); 
}
