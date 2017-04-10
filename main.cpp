#include "frmmain.h"
#include <QApplication>
#include "qtextcodec.h"
#include "qfile.h"
#include "frminput.h"
#include "frmnum.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    //QT5版本以上默认就是采用UTF-8编码
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#endif

    qApp->setFont(QFont("Microsoft YaHei", 9));

#ifndef __arm__
    //如果输入法字库文件不存在,自动拷贝字库文件
    QString path = qApp->applicationDirPath();
    QFile file(path + "/py.db");
    if (!file.exists() || file.size()==0) {
        QStringList list = path.split("/");
        QString fileName, newName;
        for (int i = 0; i < list.count() - 2; i++) {
            fileName = fileName + list.at(i) + "/";
        }
        fileName += "InputTool/py.db";
        newName = path + "/py.db";
        file.remove();
        QFile::copy(fileName, newName);
    }
#endif

    //在main函数中就加载输入法面板,保证整个应用程序可以使用输入法
    //以下方法打开中文输入法
    frmInput::Instance()->Init("control", "silvery", 10, 10);
    //以下方法打开数字键盘
    //frmNum::Instance()->Init("black", 10);

    frmMain w;
    w.showMaximized();

    return a.exec();
}
