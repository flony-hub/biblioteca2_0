#ifndef DIALOGOPRESTAMO_H
#define DIALOGOPRESTAMO_H

#include <QDialog>
#include <QDate>

namespace Ui {
class DialogoPrestamo;
}

class DialogoPrestamo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogoPrestamo(QWidget *parent = nullptr, bool esDevolucion = false);
    ~DialogoPrestamo();

    QString getIsbnLibro() const;
    QString getDniUsuario() const;
    QDate getFechaPrestamo() const;
    QDate getFechaDevolucion() const;
    void setDatosPrestamo(const QString& isbn, const QString& dni, const QDate& fechaPrestamo);

private slots:
    void on_btnAceptar_clicked();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    Ui::DialogoPrestamo *ui;
    bool m_esDevolucion;
};

#endif // DIALOGOPRESTAMO_H