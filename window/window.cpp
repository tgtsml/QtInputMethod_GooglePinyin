#include "window.h"
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", "tgtsml");

    QApplication app(argc, argv);

    window w;
    w.resize(400,300);
    w.show();

    return app.exec();
}

window::window(QWidget *parent) : QWidget(parent)
{
    QPushButton *btn = new QPushButton("test button", this);
    QLineEdit *line = new QLineEdit(this);
    QTextEdit *text = new QTextEdit(this);

    QVBoxLayout *vb = new QVBoxLayout(this);
    vb->addWidget(btn);
    vb->addWidget(line);
    vb->addWidget(text);
}
