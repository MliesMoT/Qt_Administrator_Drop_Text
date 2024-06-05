#include "dragdropwindow.h"
#include "ui_dragdropwindow.h"

#include <QDebug>
#include <Windows.h>
#include <WinUser.h>
#include <ole2.h>
#include <shellapi.h>
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"Ole32.lib")

DragDropWindow::DragDropWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DragDropWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);

//    ChangeWindowMessageFilter(WM_DROPFILES, 1);
//    qDebug() << winId() << effectiveWinId();
//    qDebug() << ChangeWindowMessageFilterEx((HWND)effectiveWinId(), WM_DROPFILES, MSGFLT_ALLOW, NULL);
//    qDebug() << ChangeWindowMessageFilterEx((HWND)effectiveWinId(), WM_COPYDATA, MSGFLT_ALLOW, NULL);
//    qDebug() << ChangeWindowMessageFilterEx((HWND)effectiveWinId(), 0x0049, MSGFLT_ALLOW, NULL);
//    DragAcceptFiles((HWND)effectiveWinId(), true);
//    qDebug() << GetLastError();
//    HRESULT res = RevokeDragDrop((HWND)winId());
//    qDebug() << "res:" <<res;
}

DragDropWindow::~DragDropWindow()
{
    delete ui;
}
