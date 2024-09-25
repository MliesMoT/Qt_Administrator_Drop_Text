对知乎问题： 
> [Qt管理员权限如何支持拖放操作？](https://www.zhihu.com/question/607474668)

涉及到的解决方案进行进一步的验证和测试，
其中主要参考 **白柳**,**藤原拓海** 的回答

使用MScv2017 64编译器 

Based on Qt 5.13.1

# 总结：
在Qt creator以管理员启动的情况下,重写拖拽事件都无效；
    
    //setAcceptDrops(true);
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;'
    
在QFrame 控件中 初始化时
    
    DragDrop_Frame::DragDrop_Frame(QWidget* parent, Qt::WindowFlags f )
    :QFrame(parent,f)
    {
    //~~//!玄学必须打印这一段 否则ChangeWindowMessageFilterEx 函数失败~~
    //~~qDebug() << winId()  << this->window()->winId() << this->window()->effectiveWinId();~~
    //! 在执行前先执行winId();effectiveWinId();两个函数，与qDebug()无关
    winId();
    this->window()->winId();
    this->window()->effectiveWinId();

    qDebug() << ChangeWindowMessageFilterEx((HWND)this->window()->effectiveWinId(), WM_DROPFILES, MSGFLT_ALLOW, NULL);
    qDebug() << ChangeWindowMessageFilterEx((HWND)this->window()->effectiveWinId(), WM_COPYDATA, MSGFLT_ALLOW, NULL);
    qDebug() << ChangeWindowMessageFilterEx((HWND)this->window()->effectiveWinId(), 0x0049, MSGFLT_ALLOW, NULL);

    //! https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-dragacceptfiles
    //! 调用 DragAcceptFiles 且 fAccept 参数设置为 TRUE 的应用程序已将自身标识为能够处理来自文件管理器 的WM_DROPFILES 消息。
    DragAcceptFiles((HWND)this->window()->effectiveWinId(), true);
    //    qDebug() << GetLastError();
    HRESULT res = RevokeDragDrop((HWND)this->window()->effectiveWinId());
    //    qDebug() << "DragDrop_Frame" <<res;

    qDebug() << ChangeWindowMessageFilterEx((HWND)winId(), WM_DROPFILES, MSGFLT_ALLOW, NULL);
    qDebug() << ChangeWindowMessageFilterEx((HWND)winId(), WM_COPYDATA, MSGFLT_ALLOW, NULL);
    qDebug() << ChangeWindowMessageFilterEx((HWND)winId(), 0x0049, MSGFLT_ALLOW, NULL);
    DragAcceptFiles((HWND)winId(), true);

    //! https://learn.microsoft.com/zh-cn/windows/win32/api/ole2/nf-ole2-revokedragdrop
    res = RevokeDragDrop((HWND)winId());
    qDebug() << "DragDrop_Frame" <<res;
    }

在配合 白柳 的 nativeEvent(const QByteArray &eventType, void *message, long *result)事件，就能实现在QFrame 控件中获取到拖拽文件路径，等一系列内容
    
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


后来尝试 **藤原拓海** 的回答，发现直接精简代码，这几行代码就可以了
    
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
