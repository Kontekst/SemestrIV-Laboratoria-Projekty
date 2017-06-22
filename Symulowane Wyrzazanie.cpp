// SADlg.cpp : implementation file
//
 
#include "stdafx.h"
#include "SA.h"
#include "SADlg.h"
#include <math.h>
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
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
// CSADlg dialog
 
CSADlg::CSADlg(CWnd* pParent /*=NULL*/)
    : CDialog(CSADlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CSADlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
 
void CSADlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CSADlg)
    DDX_Control(pDX, IDC_CITY_FRAME, m_CityFrame);
    //}}AFX_DATA_MAP
}
 
BEGIN_MESSAGE_MAP(CSADlg, CDialog)
    //{{AFX_MSG_MAP(CSADlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_START, OnStart)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
 
/////////////////////////////////////////////////////////////////////////////
// CSADlg message handlers
 
BOOL CSADlg::OnInitDialog()
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
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
   
   
    srand((unsigned)time(NULL));
 
    CRect r;
    m_CityFrame.GetClientRect(&r);
 
    m_memDC.CreateCompatibleDC(GetDC());
    m_bmp.CreateCompatibleBitmap(GetDC(), r.Width(), r.Height());
    m_font.CreatePointFont(110, L"Arial");
    m_pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    m_brush.CreateSolidBrush(RGB(255, 255, 255));
   
    m_memDC.SelectObject(&m_bmp);
    m_memDC.SelectObject(&m_font);
    m_memDC.SelectObject(&m_pen);
    m_memDC.SelectObject(&m_brush);
 
    m_CityFrame.GetClientRect(&r);
    m_memDC.Rectangle(&r);
 
    m_memDC.SetBkMode(TRANSPARENT);
   
    COLORREF oldTxtCol = (m_memDC.SetTextColor(RGB (0, 100, 10)));
   
    return TRUE;  // return TRUE  unless you set the focus to a control
}
 
void CSADlg::OnSysCommand(UINT nID, LPARAM lParam)
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
 
void CSADlg::OnPaint()
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
        CPaintDC dc(this); // device context for painting
 
        CRect r;
        m_CityFrame.GetWindowRect(&r);
        ScreenToClient(r);     
 
        dc.BitBlt(r.left, r.top, r.right - r.left, r.bottom - r.top, &m_memDC, 0, 0, SRCCOPY);
   
        CDialog::OnPaint();
    }
}
 
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSADlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}
 
/**************************************************************************}
{ODCZYT MAPY Z PLIKU, WYZNACZENIE TEMPERATURY POCZATKOWEJ                  }
{**************************************************************************/
BOOL CSADlg::InitializeMap()
{
 
    int i, j, k;
   
    int stop;
 
    CFile f;
    if (!f.Open(L"tsp-c.dat", CFile::modeRead | CFile::shareDenyWrite))
    {
        MessageBox(L"Proszê umieœciæ plik tsp-c.dat w katalogu, w którym znajduje siê program.");
        return FALSE;
    }
   
    float fBuf;
 
    for (i = 0; i < NCITIES; i++)
    {
        f.Read(&fBuf, sizeof(float));
        loc[i][0] = (double)fBuf;
        f.Read(&fBuf, sizeof(float));
        loc[i][1] = (double)fBuf;
    };
 
    f.Close();
    for (j = 0; j < NCITIES; j++)
    {
        do
        {
            stop = 1;
            route[j] = rand() % NCITIES;
            k=0;
         
            while (k<j)
            {
                if (route[k] == route[j]) stop = 0;
                k++;
            };
        }
        while (!stop);
     };
 
     T = 15.0;
     energy = 0;
 
     return TRUE;
}
 
/**************************************************************************}
{RYSOWANIE AKTUALNEJ TRASY, WYSWIETLANIE ENERGII                           }
{**************************************************************************/
void CSADlg::Draw()
{
 
    int i, x, y, x1, y1;
    char s[10];
    CString sEn = "Energia: ";
 
    CRect r;
    m_CityFrame.GetClientRect(&r);
    m_memDC.Rectangle(&r);
 
    if (energy == 0.0)
    {
        sEn = "Oblicz wartoœæ energii!";
    }
    else
    {
        _gcvt_s(s, sizeof(s), energy,5);
        sEn += CString(s);
    }
 
    m_memDC.TextOut(10, r.Height()-20, sEn);
 
    for (i = 0; i < NCITIES; i++)
    {
        x = 10 + (int)((r.Width()-20)*loc[i][0]);
        y = 10 + (int)((r.Height()-20)*loc[i][1]);
        m_memDC.Ellipse(x-5, y-5, x+5, y+5);
    }
 
    for (i = 0; i < NCITIES-1; i++)
    {
        x = 10 + (int)((r.Width()-20)*loc[route[i]][0]);
        y = 10 + (int)((r.Height()-20)*loc[route[i]][1]);
        x1 = 10 + (int)((r.Width()-20)*loc[route[i+1]][0]);
        y1 = 10 + (int)((r.Height()-20)*loc[route[i+1]][1]);
        m_memDC.MoveTo(x, y);
        m_memDC.LineTo(x1, y1);
    };
 
    x = 10 + (int)((r.Width()-20)*loc[route[NCITIES-1]][0]);
    y = 10 + (int)((r.Height()-20)*loc[route[NCITIES-1]][1]);
    x1 = 10 + (int)((r.Width()-20)*loc[route[0]][0]);
    y1 = 10 + (int)((r.Height()-20)*loc[route[0]][1]);
    m_memDC.MoveTo(x, y);
    m_memDC.LineTo(x1, y1);
 
    CDC* pDC = GetDC();
    m_CityFrame.GetWindowRect(&r);
    ScreenToClient(r);
 
    pDC->BitBlt(r.left, r.top, r.right - r.left, r.bottom - r.top, &m_memDC, 0, 0, SRCCOPY);
 
    ReleaseDC(pDC);
}
 
void CSADlg::OnStart()
{
 
    if (!InitializeMap())
        return;
 
    Draw();
 
    maxTrialN=NCITIES*100;
    maxAcceptN=NCITIES*10;
    stopTolerance=0.005;
   
    int licznikProb = 0;
    int licznikZaakceptowanychProb = 0;
    do{
        minE = 1e20;
        maxE = -1;
 
        licznikProb = 0;
        licznikZaakceptowanychProb = 0;
        double aktualnaSumaTrasy = 0.0;
        //----- Obliczenie energii aktualnego rozwiazania -----//
        /*      for (int i = 0; i < (NCITIES - 1); i++){
                    aktualnaSumaTrasy += sqrt((loc[[i]][0] - loc[ + 1][0])*(loc[i][0] - loc[i + 1][0]) + (loc[i][1] - loc[i + 1][1])*(loc[i][1] - loc[i + 1][1]));
                    }
                    aktualnaSumaTrasy += sqrt((loc[0][0] - loc[NCITIES - 1][0])*(loc[0][0] - loc[NCITIES - 1][0]) + (loc[0][1] - loc[NCITIES - 1][1])*(loc[0][1] - loc[NCITIES - 1][1]));
                    */
        for (int i = 0; i < (NCITIES - 1); i++){
            aktualnaSumaTrasy += sqrt((loc[route[i]][0] - loc[route[i + 1]][0])*(loc[route[i]][0] - loc[route[i + 1]][0]) + (loc[route[i]][1] - loc[route[i + 1]][1])*(loc[route[i]][1] - loc[route[i + 1]][1]));
        }
        aktualnaSumaTrasy += sqrt((loc[route[0]][0] - loc[route[NCITIES - 1]][0])*(loc[route[0]][0] - loc[route[NCITIES - 1]][0]) + (loc[route[0]][1] - loc[route[NCITIES - 1]][1])*(loc[route[0]][1] - loc[route[NCITIES - 1]][1]));
 
        //----- Zamiana dwoch miast -----//
        do{
            int pierwszeMiasto = rand() % NCITIES;
            int drugieMiasto;
            do{
                drugieMiasto = rand() % NCITIES;
            } while (pierwszeMiasto == drugieMiasto);
 
            int temp = route[pierwszeMiasto];
            route[pierwszeMiasto] = route[drugieMiasto];
            route[drugieMiasto] = temp;
 
            /*loc[pierwszeMiasto][0];
            int tempy = loc[pierwszeMiasto][1];
            loc[pierwszeMiasto][0] = loc[drugieMiasto][0];
            loc[pierwszeMiasto][1] = loc[drugieMiasto][1];
            loc[drugieMiasto][0] = tempx;
            loc[drugieMiasto][1] = tempy;*/
            //----- -----//
            double nowaSumaTrasy = 0.0;
            for (int i = 0; i < (NCITIES - 1); i++){
                nowaSumaTrasy += sqrt((loc[route[i]][0] - loc[route[i + 1]][0])*(loc[route[i]][0] - loc[route[i + 1]][0]) + (loc[route[i]][1] - loc[route[i + 1]][1])*(loc[route[i]][1] - loc[route[i + 1]][1]));
            }
            nowaSumaTrasy += sqrt((loc[route[0]][0] - loc[route[NCITIES - 1]][0])*(loc[route[0]][0] - loc[route[NCITIES - 1]][0]) + (loc[route[0]][1] - loc[route[NCITIES - 1]][1])*(loc[route[0]][1] - loc[route[NCITIES - 1]][1]));
 
            /* 5. Zaakceptuj nowe rozwi¹zanie z prawdopodobieñstwem 1/(1+exp(dE/T)), gdzie
            (dE = En-E). W przypadku zaakceptowania zwiêksz licznik zaakceptowanych prób.*/
 
            double dN = aktualnaSumaTrasy - nowaSumaTrasy;
 
            double wylosowanLiczbaOdZeraDoJedn = ((double)rand() / (RAND_MAX));
 
            double prawdopodobienstwo = 1.0 / (1.0 + pow(dN, T));
 
            if (wylosowanLiczbaOdZeraDoJedn < prawdopodobienstwo){//Akceptujemy zamiane
                licznikZaakceptowanychProb++;
                if (nowaSumaTrasy > maxE)
                    maxE = nowaSumaTrasy;
 
                if (nowaSumaTrasy < minE)
                    minE = nowaSumaTrasy;
            }
            else{
                temp = route[pierwszeMiasto];
                route[pierwszeMiasto] = route[drugieMiasto];
                route[drugieMiasto] = temp;
            }
            licznikProb++;
 
        } while (licznikProb < maxTrialN || licznikZaakceptowanychProb < maxAcceptN);
 
        energy = minE;
        Draw();
        T *= 0.5;
    } while ((maxE - minE) / maxE  > stopTolerance);
 
 
  /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!}
  {TU WSTAWIC PETLE WYZARZANIA                                               }
  {!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!}
  Z pliku zosta³a wczytana mapa miast. Jest ich NCITIES. Ich wspó³rzêdne     
  zawiera tablica loc[NCITIES][2]. Ka¿dy wiersz tej tablicy to wspó³rzêdne
  (x,y) jednego miasta.
 
  Losowo wybrana trasa jest umieszczona w tablicy route[NCITIES].
  Trasa to ci¹g liczb oznaczaj¹cych miasta i jednoczeœnie wskazuj¹cych wiersze
  tablicy 'loc' (aby mo¿na by³o odczytywaæ wspó³rzêdne miast).
 
  Procedura 'Draw' wyœwietla trasê zawart¹ w 'route' i wartoœæ zmiennej         
  'energy' (o ile jest wyznaczona).
  Temperatura pocz¹tkowa jest ustawiona w zmiennej 'T'.
 
  Zmienne minE i maxE s³u¿¹ do przechowywania energii najlepszego
  i najgorszego rozwi¹zania, zaakceptowanego w danym kroku (czyli przy
  tej samej temperaturze). Sprawdzaj¹c wartoœæ ró¿nicy maxE-minE
  mo¿na podejmowaæ decyzjê o zakoñczeniu b¹dŸ kontynuowaniu wy¿arzania.
 
  Zmienne s¹ zdefiniowane w pliku SADlg.h.
 
  ---Algorytm symulowanego wy¿arzania---
 
  Poni¿sze kroki nale¿y powtarzaæ, dopóki (maxE-minE)/maxE nie spadnie
  poni¿ej progu okreœlonego przez stopTolerance.
 
1. Ustaw licznik prób i licznik zaakceptowanych prób na 0.
2. Oblicz energiê E aktualnego rozwi¹zania.
3. Wyznacz nowe rozwi¹zanie (np. zamieniaj¹c miejscami dwa miasta w trasie).
4. Oblicz energiê En nowego rozwi¹zania.
5. Zaakceptuj nowe rozwi¹zanie z prawdopodobieñstwem 1/(1+exp(dE/T)), gdzie
   (dE = En-E). W przypadku zaakceptowania zwiêksz licznik zaakceptowanych prób.
6. Uaktualnij maxE i minE, jeœli jest to konieczne.
7. Zwiêksz licznik prob. Je¿eli licznik prób lub licznik zaakceptowanych prób
   osi¹gnê³y maksymaln¹ wartoœæ (maxTrialN, maxAcceptN), idŸ do kroku 8. W przeciwnym razie wróæ do kroku 3.
8. Uaktualnij zawartoœæ zmiennych 'route' i 'energy', tak by opisywa³y ostatni¹ zaakceptowan¹ trasê.
9. Wywo³aj funkcjê 'Draw', aby uzyskaæ podgl¹d aktualnego rozwi¹zania.
10.Obni¿ temperaturê.
 
  {!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
 
   
}