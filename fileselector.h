#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include <QDialog>
#include <QtCore>
#include <QtWidgets>

/*!
 * \class FileSelector
 * Primo QDialog che si vede all' avvio dell' applicazione,
 * consente di scegliere la locazione del file di salvataggio JSON,
 * per poi ritornare il controllo a MainWindow.
 * Il tutto tramite una singola chiamata ad un metoddo statico
 */
class FileSelector : public QDialog {
    Q_OBJECT
private:
    QString &path;
    // costruttore privato!! non instanziabile direttamente
    FileSelector(QWidget *parent, QString& path);

public:
    /*
     * La classe si instanzia tramite un metodo statico
     * che ritorna la stringa richiesta a MainWindow.
     * Molto simile a dialoghi natii di Qt che usano la stessa tecnica.
     */
    static QString getPathFromUserInput();

};

#endif // FILESELECTOR_H
