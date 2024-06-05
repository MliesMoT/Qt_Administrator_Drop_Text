#ifndef DRAGDROP_FRAME_H
#define DRAGDROP_FRAME_H
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

#include <QObject>
#include <QFrame>

#include <Windows.h>
#include <shellapi.h>
#include <QDebug>

class DragDrop_Frame:public QFrame
{
public:
    DragDrop_Frame(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void dragEnterEvent(QDragEnterEvent *e) ;
    bool nativeEvent(const QByteArray &eventType, void *message, long *result){
        if (eventType == "windows_generic_MSG"){
            PMSG msg = (PMSG) message;
            if(msg->message == 563){
                qDebug() << msg->message << msg->hwnd << msg->wParam << msg->lParam << msg->time << msg->pt.x << msg->pt.y;
                UINT file_num = DragQueryFile((HDROP) msg->wParam, 0xFFFFFFFF, NULL, 0);
                qDebug() << "文件数量:" << file_num;
                for(int i=0;i<(int)file_num;i++){
                    UINT file_name_size = DragQueryFile((HDROP) msg->wParam, i, NULL, 0);
                    qDebug() << file_name_size;
                    LPWSTR  fn = (LPWSTR)malloc(sizeof(WCHAR)*file_name_size);
                    //! https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-dragqueryfilew
                    UINT code = DragQueryFileW((HDROP) msg->wParam, i, fn, file_name_size);
                    QString filename = QString::fromStdWString(fn);
                    free(fn);
                    qDebug() << "第" << i << "个文件:" << filename;
                    qDebug() << "get name error:" << code;
                }
                qDebug() << eventType << message << *result;
            }
        }
        return QFrame::nativeEvent(eventType, message, result);
    }
};

#endif // DRAGDROP_FRAME_H
