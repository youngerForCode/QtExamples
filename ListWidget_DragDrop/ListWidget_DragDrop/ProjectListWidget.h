#ifndef PROJECTLISTWIDGET_H
#define PROJECTLISTWIDGET_H

#include <QListWidget>
#include <QPoint>
class ProjectListWidget :public QListWidget
{
	Q_OBJECT
public:
    ProjectListWidget(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *e);
    void dropEvent(QDropEvent *event);
private:
    void performDrag();
    QPoint _startPos;
};

#endif
