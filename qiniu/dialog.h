#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QPoint>
#include <QRect>
#include "json.h"
#include <QProcess>
#include <QItemSelection>
#include <QTextEdit>
#include <QFileInfo>
#include <QRegExp>
#include <QMessageBox>
#include <QStringListModel>
#include <QClipboard>
#include <QUrl>
#include <QByteArray>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QString access_key;     //七牛AK
    QString secret_key;     //七牛SK
    QString bucket;         //七牛空间
    QString src;            //保存目录
    void setparamwithedit();        //从textedit设置上面的4个参数
    QString readFile(const QString &filename); //用于读取json文件
    QString getsubstring(QString str);  //用于找到匹配(.*)=(.*)的键-值得值(value)

private slots:
    void on_saveconfig_clicked();  //更新json文件
    void on_upload();   //拖拽上传到七牛


    void on_pushButton_clicked();   //外链生成

private:
    Ui::Dialog *ui;

    // QWidget interface
protected:
    //拖拽overwrite
    void dragEnterEvent(QDragEnterEvent * e);
    void dropEvent(QDropEvent *e);
};

#endif // DIALOG_H
