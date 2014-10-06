#include "dialog.h"
#include "ui_dialog.h"

using QtJson::JsonObject;
using QtJson::JsonArray;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    //读取json文件  使用https://github.com/gaudecker/qt-json
    QString json = readFile("conf.json");
    if (json.isEmpty()) {
        qFatal("Could not read JSON file!");
        return ;
    }
    bool ok;
    JsonObject result = QtJson::parse(json, ok).toMap();
    if (!ok) {
        qFatal("An error occurred during parsing");
        return ;
    }


    QString dest =result["dest"].toString();
    QStringList list= dest.split("&");


    ui->akEdit->setPlainText(getsubstring(list.at(0)));
    ui->skEdit->setPlainText(getsubstring(list.at(1)));
    ui->bucketEdit->setPlainText(getsubstring(list.at(2)));
    ui->srcEdit->setPlainText(result["src"].toString());

    this->src=result["src"].toString();

}

Dialog::~Dialog()
{
    delete ui;
}



void Dialog::setparamwithedit()
{
    QString  ak= ui->akEdit->toPlainText();
    QString  editbucket= ui->bucketEdit->toPlainText();
    QString  sk= ui->skEdit->toPlainText();
    QString  editsrc= ui->srcEdit->toPlainText();

    this->access_key=ak;
    this->secret_key=sk;
    this->bucket=editbucket;
    this->src=editsrc;

}

QString Dialog::readFile(const QString &filename)
{
    QFile f(filename);
    if (!f.open(QFile::ReadOnly | QFile::Text)) {
        return QString();
    } else {
        QTextStream in(&f);
        return in.readAll();
    }

}

QString Dialog::getsubstring(QString str)
{

    QString pattern("(.*)=(.*)");
    QRegExp rx(pattern);
    int pos = str.indexOf(rx);
    if ( pos >= 0 )
    {
        return rx.cap(2);
    }


}

void Dialog::on_saveconfig_clicked()
{
    setparamwithedit();
    QtJson::JsonObject contributor;
    contributor["debug_level"] = 1;
    contributor["deletable"] = 0;
    contributor["dest"] = "qiniu:access_key="+this->access_key+"&secret_key="+ this->secret_key+"&bucket="+this->bucket;
    contributor["src"] = src.toStdString().c_str();

    QFile file("conf.json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return ;

    QTextStream out(&file);
    out<<QtJson::serialize(contributor);;

}

void Dialog::on_upload()
{

    QProcess *pProces = (QProcess *)sender();
    QString result = pProces->readAll();
    qDebug()<<result;
}




void Dialog::dragEnterEvent(QDragEnterEvent * e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }

}

void Dialog::dropEvent(QDropEvent *e)
{

    QPoint p= e->pos();

    //两个label，一个拖拽设置上传目录，一个拖拽上传文件
    QPoint lp= ui->labeldrag->pos();
    QPoint lpupload= ui->labelupload->pos();

//    两个label所在区域
    QRect r(lp.x(),lp.y(),ui->labeldrag->width(),ui->labeldrag->height());
    QRect rupload(lpupload.x(),lpupload.y(),ui->labelupload->width(),ui->labelupload->height());


//    区域1，设置上传目录
    if(r.contains(p)){
        foreach (const QUrl &url, e->mimeData()->urls()) {
            const QString &fileName = url.toLocalFile();
            qDebug()<<fileName;
            QFileInfo info(fileName);
            if(info.isDir()){
                qDebug()<<"is dir";
                ui->srcEdit->setPlainText(fileName);

            }
            if(info.isFile()){
                qDebug()<<"is file";
            }

        }
    }
//区域2，设置上传
    if(rupload.contains(p)){
        foreach (const QUrl &url, e->mimeData()->urls()) {
            const QString &fileName = url.toLocalFile();
            QFile::copy(fileName, ui->srcEdit->toPlainText()+"/"+url.fileName());
            ui->listWidget->addItem(url.fileName());

        }
//调用upload.bat / .sh
        QProcess *pProces = new QProcess(this);
        connect(pProces, SIGNAL(readyRead()),this, SLOT(on_upload()));
        QStringList  list;
        //list<<"conf.json";
        pProces->start("./upload.sh", list);//for macox
    }
}



void Dialog::on_pushButton_clicked()
{
    QString outurl;
    outurl="http://"+ui->bucketEdit->toPlainText()+".qiniudn.com/"+
            (QUrl::toPercentEncoding(ui->listWidget->currentItem()->text())).constData();
   // QByteArray ba = QUrl::toPercentEncoding(outurl);
    if(outurl.length()==0){
        ui->lineEdit->setText("请选中文件");
    }
    ui->lineEdit->setText(outurl);
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(outurl);

}
