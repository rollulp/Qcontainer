#include "fileselector.h"
#include <QFileDialog>
#include <QKeyEvent>
#include <QDir>

FileSelector::FileSelector(QWidget *parent, QString &path) :
    QDialog(parent), path(path)
{
    setWindowTitle("Save file");

    path = "@nopath@";

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel;
    QHBoxLayout *hor = new QHBoxLayout;
    QLineEdit *lineEdit = new QLineEdit;
    QPushButton *browse = new QPushButton("Open");
    QDialogButtonBox * bb = new QDialogButtonBox;
    bb->setOrientation(Qt::Horizontal);
    bb->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    label->setText("Select a save file :");
    lineEdit->setText(QDir::homePath() + "/QcontainerData.json");

    layout->addWidget(label);
    hor->addWidget(lineEdit);
    hor->addWidget(browse);
    layout->addLayout(hor);
    layout->addWidget(bb);

    connect(browse, &QPushButton::clicked, [lineEdit, this] () {
        lineEdit->setText( QFileDialog::getOpenFileName(this, "Open File", "/home", "SaveFile (*.json)") );
    });
    connect(bb, &QDialogButtonBox::accepted, [lineEdit, this] () {
        this->path = lineEdit->text();
        this->close();
    });
    connect(bb, &QDialogButtonBox::rejected, [lineEdit, this] () {
        this->path = "@nopath@";
        this->close();
    });

    resize(450, 99);


}

/*!
 * \brief funzione locale per validare il percorso
 * \param path la stringa da validare
 * \return se è valida o meno
 * qui c'è l'unico goto del software, evitabile ma carino
 */
static bool validate(QString & path) {
    QFileInfo fi(path);
    if (fi.isDir()) {
        if (path[path.length()-1] == '/')
            path = path + '/';
        path = path + "QcontainerData.json";
    } else {
        fi.setFile(fi.dir().path());
        if (fi.isDir())
            goto unGotoVaMessoSempre;
        return false;
    }
    unGotoVaMessoSempre:
    if (!path.endsWith(".json"))
        return false;
    return fi.isWritable();
}

QString FileSelector::getPathFromUserInput() {
    QString path;
    do {
        FileSelector *fileSelector = new FileSelector(nullptr, path);
        fileSelector->exec();
    } while ( path != "@nopath@" && !validate(path) && QMessageBox::information(0, "Invalid path", "Please select a valid path that ends with .json") );

    return path;
}

