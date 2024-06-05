#ifndef DRAGDROPWINDOW_H
#define DRAGDROPWINDOW_H
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

#include <QMainWindow>

namespace Ui {
class DragDropWindow;
}

class DragDropWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DragDropWindow(QWidget *parent = nullptr);
    ~DragDropWindow();

private:
    Ui::DragDropWindow *ui;
};

#endif // DRAGDROPWINDOW_H
