#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include <QDialog>

namespace Ui {
class FileSelector;
}

class FileSelector : public QDialog
{
    Q_OBJECT

public:
    explicit FileSelector(QWidget *parent = 0);
    ~FileSelector();

    QString getFilePath() const;
    void keyPressEvent(QKeyEvent *e);

private slots:
    void on_pushButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::FileSelector *ui;
};

#endif // FILESELECTOR_H
