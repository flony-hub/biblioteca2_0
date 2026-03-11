#include "dialogoprestamo.h"
#include "ui_dialogoprestamo.h"
#include <QMessageBox>
#include <QPaintEvent>
#include <QPainter>

DialogoPrestamo::DialogoPrestamo(QWidget *parent, bool esDevolucion) :
    QDialog(parent),
    ui(new Ui::DialogoPrestamo),
    m_esDevolucion(esDevolucion)
{
    ui->setupUi(this);

    // Conecta el botón Aceptar al slot on_btnAceptar_clicked
    connect(ui->btnAceptar, &QPushButton::clicked, this, &DialogoPrestamo::on_btnAceptar_clicked);

    // Configuración inicial según si es préstamo o devolución
    if (m_esDevolucion) {
        setWindowTitle("Registrar Devolución");
        ui->dateEditPrestamo->setEnabled(false);
        ui->dateEditDevolucion->setDate(QDate::currentDate());
    } else {
        setWindowTitle("Realizar Préstamo");
        ui->dateEditPrestamo->setDate(QDate::currentDate());
        ui->dateEditDevolucion->setDate(QDate::currentDate().addDays(7));
    }
}

void DialogoPrestamo::paintEvent(QPaintEvent *event)
{
    QDialog::paintEvent(event);
    
    QPainter painter(this);
    painter.setOpacity(0.2);
    
    QPixmap watermark(":/images/logo_marca_agua.png");
    watermark = watermark.scaled(width()/4, height()/4, Qt::KeepAspectRatio);
    
    int x = (width() - watermark.width()) / 2;
    int y = (height() - watermark.height()) / 2;
    painter.drawPixmap(x, y, watermark);
}

DialogoPrestamo::~DialogoPrestamo()
{
    delete ui;
}

QString DialogoPrestamo::getIsbnLibro() const
{
    return ui->lineEditISBN->text().trimmed();
}

QString DialogoPrestamo::getDniUsuario() const
{
    return ui->lineEditDNI->text().trimmed();
}

QDate DialogoPrestamo::getFechaPrestamo() const
{
    return ui->dateEditPrestamo->date();
}

QDate DialogoPrestamo::getFechaDevolucion() const
{
    return ui->dateEditDevolucion->date();
}

void DialogoPrestamo::setDatosPrestamo(const QString& isbn, const QString& dni, const QDate& fechaPrestamo)
{
    ui->lineEditISBN->setText(isbn);
    ui->lineEditDNI->setText(dni);
    ui->dateEditPrestamo->setDate(fechaPrestamo);
    ui->lineEditISBN->setEnabled(false);
    ui->lineEditDNI->setEnabled(false);
    ui->dateEditPrestamo->setEnabled(false);
}

void DialogoPrestamo::on_btnAceptar_clicked()
{
    if (getIsbnLibro().isEmpty() || getDniUsuario().isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Debe completar todos los campos");
        return;
    }

    if (!m_esDevolucion && getFechaDevolucion() <= getFechaPrestamo()) {
        QMessageBox::warning(this, "Advertencia", "La fecha de devolución debe ser posterior a la de préstamo");
        return;
    }

    accept();
}
