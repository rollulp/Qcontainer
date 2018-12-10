#include "fileselector.h"
#include "ui_fileselector.h"
#include <QFileDialog>
#include <QKeyEvent>

FileSelector::FileSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileSelector)
{
    ui->setupUi(this);
    this->setWindowTitle("Save file");
}

FileSelector::~FileSelector()
{
    delete ui;
}

QString FileSelector::getFilePath() const
{
    return ui->lineEdit->text();
}

void FileSelector::keyPressEvent(QKeyEvent *e)
{
    if (e->key() != Qt::Key_Escape)
        QDialog::keyPressEvent(e);
}

void FileSelector::on_pushButton_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "/home", "SaveFile (*.json)");
    ui->lineEdit->setText(fileName);
}


void FileSelector::on_buttonBox_accepted()
{
    QCoreApplication::exit(1);
}
