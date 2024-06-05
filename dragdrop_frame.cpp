#include "dragdrop_frame.h"
#include <QDebug>
#include "drophandler.h"
#include <QDragEnterEvent>
#include <QMimeData>

DragDrop_Frame::DragDrop_Frame(QWidget* parent, Qt::WindowFlags f )
    :QFrame(parent,f)
{
    this->setAcceptDrops(true);
    setStyleSheet("QFrame { "
                  "border-radius: 24px;"
                  "border: 2px dashed #676E89;"
                  "background-image: url(:/tuozhuai.png);"
                  "background-position: center;"
                  "background-repeat: no-repeat;"
                  "background-origin: content;"
                  " }");

//    ChangeWindowMessageFilter(WM_DROPFILES, 1);

    //! ==========================================================
    //! 测试版本1
//    //!玄学 必须打印这一段 否则ChangeWindowMessageFilterEx 函数失败
//    qDebug() << winId()  << this->window()->winId() << this->window()->effectiveWinId();
//    qDebug() << ChangeWindowMessageFilterEx((HWND)this->window()->effectiveWinId(), WM_DROPFILES, MSGFLT_ALLOW, NULL);
//    qDebug() << ChangeWindowMessageFilterEx((HWND)this->window()->effectiveWinId(), WM_COPYDATA, MSGFLT_ALLOW, NULL);
//    qDebug() << ChangeWindowMessageFilterEx((HWND)this->window()->effectiveWinId(), 0x0049, MSGFLT_ALLOW, NULL);
//    //! https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-dragacceptfiles
//    //! 调用 DragAcceptFiles 且 fAccept 参数设置为 TRUE 的应用程序已将自身标识为能够处理来自文件管理器 的WM_DROPFILES 消息。
//    DragAcceptFiles((HWND)this->window()->effectiveWinId(), true);
////    qDebug() << GetLastError();
//    HRESULT res = RevokeDragDrop((HWND)this->window()->effectiveWinId());
////    qDebug() << "DragDrop_Frame" <<res;
//    qDebug() << ChangeWindowMessageFilterEx((HWND)winId(), WM_DROPFILES, MSGFLT_ALLOW, NULL);
//    qDebug() << ChangeWindowMessageFilterEx((HWND)winId(), WM_COPYDATA, MSGFLT_ALLOW, NULL);
//    qDebug() << ChangeWindowMessageFilterEx((HWND)winId(), 0x0049, MSGFLT_ALLOW, NULL);
//    DragAcceptFiles((HWND)winId(), true);
//    //! https://learn.microsoft.com/zh-cn/windows/win32/api/ole2/nf-ole2-revokedragdrop
//    res = RevokeDragDrop((HWND)winId());
//    qDebug() << "DragDrop_Frame" <<res;



     //! ==========================================================
     //! 测试2
     //! 在不使用 管理员权限启动时
     //! DropHandler 类能监控拖拽事件，
     //! 重写 dragEnterEvent系列事件也可以，所以基本没用
     //! https://learn.microsoft.com/zh-cn/windows/win32/api/ole2/nf-ole2-registerdragdrop
     //qDebug() << RegisterDragDrop((HWND)winId(),new DropHandler(NULL));


    //! ==========================================================
    //! 测试 藤原拓海 回答
    //! 调用winId()后会将Qt窗口转为win原生窗口 可能会产生部分显示问题  ---测试时没遇到，
    //1.是先使用RevokeDragDrop取消掉注册
    qDebug() << winId()  << this->window()->winId() << this->window()->effectiveWinId();
    qDebug() <<RevokeDragDrop((HWND)this->window()->effectiveWinId());
    //2.DragAcceptFiles注册窗口接收拖拽事件
    //--3.SetWindowLongA()设置窗口及事件回调函数-- //不需要
    DragAcceptFiles((HWND)this->window()->effectiveWinId(), true);
    DragAcceptFiles((HWND)winId(), true);
    //在 nativeEvent(const QByteArray &eventType, void *message, long *result) 事件中实现
    //4.在事件回调中处理563消息（WM_DROPFILES）消息。
    //5.再使用DragQueryFileA获取文件路径信息
    qDebug() << ChangeWindowMessageFilterEx((HWND)winId(), WM_DROPFILES, MSGFLT_ALLOW, NULL);
    qDebug() << ChangeWindowMessageFilterEx((HWND)winId(), WM_COPYDATA, MSGFLT_ALLOW, NULL);
    qDebug() << ChangeWindowMessageFilterEx((HWND)winId(), 0x0049, MSGFLT_ALLOW, NULL);


}


void DragDrop_Frame::dragEnterEvent(QDragEnterEvent *e){
    qDebug()<<"[mimeData] "<< e->mimeData()->urls().count();
}

