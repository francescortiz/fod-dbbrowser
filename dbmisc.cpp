#include "dbmisc.h"
#include <QWidget>

DBMisc::DBMisc()
{
}

void DBMisc::setWidgetStyleSheet(QWidget *widget) {
    QColor bgColor  = widget->palette().background().color();
    QString bgRGB = "rgb("+QString::number(bgColor.red())+","+QString::number(bgColor.green())+","+QString::number(bgColor.blue())+")";
    widget->setStyleSheet(" QLineEdit:disabled,QListView:disabled,QTableView:disabled,QTextEdit:disabled { background:"+bgRGB+"; }");
}
