#include "ProjectListWidget.h"
#include <QtGui>
#include <QApplication>

ProjectListWidget::ProjectListWidget(QWidget *parent):QListWidget(parent)
{
    setAcceptDrops(true);
}

void ProjectListWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
		_startPos = event->pos();
    return QListWidget::mousePressEvent(event);
}

void ProjectListWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        auto shiftPos = (e->pos()- _startPos);
        int length = shiftPos.manhattanLength();
        if(length > QApplication::startDragDistance())
            performDrag();
    }
    QListWidget::mouseMoveEvent(e);
}

void ProjectListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    ProjectListWidget *source = qobject_cast<ProjectListWidget *>(event->source());
    if(source && source != this)
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }

}

void ProjectListWidget::dragMoveEvent(QDragMoveEvent *event)
{
    ProjectListWidget *source = qobject_cast<ProjectListWidget *>(event->source());
    if(source && source != this)
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void ProjectListWidget::dropEvent(QDropEvent *event)
{
    ProjectListWidget *source = qobject_cast<ProjectListWidget *>(event->source());
    if(source && source != this)
    {
        addItem(event->mimeData()->text());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void ProjectListWidget::performDrag()
{
    QListWidgetItem *item = currentItem();
    if(item)
    {
        QMimeData *mimeData = new QMimeData;
        mimeData->setText(item->text());

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(QPixmap("./image/person.png"));
        if(drag->exec(Qt::MoveAction)== Qt::MoveAction)
            delete item;
    }
}
