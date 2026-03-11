#include "dialogolibro.h"
#include "ui_dialogolibro.h"
#include <QMessageBox>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include <QToolTip>


DialogoLibro::DialogoLibro(QWidget *parent, Modo modo, const Libro* libroExistente)
    : QDialog(parent), ui(new Ui::DialogoLibro), m_modo(modo)
{
    ui->setupUi(this);

    // Configuración inicial según el modo
    switch(m_modo) {
    case Buscar:
        configurarModoBusqueda();
        break;
    case Editar:
        configurarModoEdicion(libroExistente);
        break;
    case Nuevo:
    default:
        configurarModoNuevo();
    }

    // Conexiones de botones
    connect(ui->btnBuscar, &QPushButton::clicked, this, &DialogoLibro::onBuscarClicked);
    connect(ui->btnLimpiar, &QPushButton::clicked, this, &DialogoLibro::onLimpiarClicked);
    connect(ui->btnAceptar, &QPushButton::clicked, this, &DialogoLibro::accept);
    connect(ui->btnCancelar, &QPushButton::clicked, this, &DialogoLibro::reject);
    connect(ui->lineEditIsbn, &QLineEdit::textChanged, this, &DialogoLibro::validarCampos);
    connect(ui->lineEditTitulo, &QLineEdit::textChanged, this, &DialogoLibro::validarCampos);
    connect(ui->lineEditAutor, &QLineEdit::textChanged, this, &DialogoLibro::validarCampos);
    connect(ui->lineEditEditorial, &QLineEdit::textChanged, this, &DialogoLibro::validarCampos);
    connect(ui->lineEditPais, &QLineEdit::textChanged, this, &DialogoLibro::validarCampos);
    connect(ui->spinBoxAnio, QOverload<int>::of(&QSpinBox::valueChanged), this, &DialogoLibro::validarCampos);

}

void DialogoLibro::paintEvent(QPaintEvent *event)
{
    QDialog::paintEvent(event);
    
    QPainter painter(this);
    
    // Configuración ajustable
    qreal opacity = 0.95; // Transparencia (0.0 a 1.0)
    double sizeRatio = 0.6; // Tamaño relativo a la ventana (0.1 a 1.0)
    QPoint offset(10, 50); // Desplazamiento desde el centro
    
    painter.setOpacity(opacity);
    
    QPixmap watermark(":/images/logo_marca_agua.png");
    
    // Escalar manteniendo aspecto, con tamaño proporcional a la ventana
    int targetSize = qMin(width(), height()) * sizeRatio;
    watermark = watermark.scaledToWidth(targetSize, Qt::SmoothTransformation);
    
    // Posicionamiento centrado con posible offset
    int x = (width() - watermark.width()) / 2 + offset.x();
    int y = (height() - watermark.height()) / 2 + offset.y();
    
    painter.drawPixmap(x, y, watermark);
}

DialogoLibro::~DialogoLibro()
{
    delete ui;
}

void DialogoLibro::configurarModoBusqueda()
{
    setWindowTitle("Buscar Libro");
    setCamposEditables(false);
    ui->btnAceptar->setEnabled(false);
    ui->btnBuscar->setVisible(true);
    ui->btnLimpiar->setVisible(true);
}

void DialogoLibro::configurarModoEdicion(const Libro* libro)
{
    setWindowTitle("Editar Libro");
    setCamposEditables(true);
    ui->btnBuscar->setVisible(false);
    ui->btnLimpiar->setVisible(false);

    if (libro) {
        ui->lineEditIsbn->setText(libro->isbn());
        ui->lineEditTitulo->setText(libro->titulo());
        ui->lineEditAutor->setText(libro->autor());
        ui->lineEditEditorial->setText(libro->editorial());
        ui->spinBoxAnio->setValue(libro->anio());
        ui->lineEditPais->setText(libro->pais());
    }
}

void DialogoLibro::configurarModoNuevo()
{
    setWindowTitle("Nuevo Libro");
    setCamposEditables(true);
    ui->btnBuscar->setVisible(false);
    ui->btnLimpiar->setVisible(false);
    validarCampos();

}

void DialogoLibro::setCamposEditables(bool editable)
{
    ui->lineEditTitulo->setEnabled(editable);
    ui->lineEditAutor->setEnabled(editable);
    ui->lineEditEditorial->setEnabled(editable);
    ui->spinBoxAnio->setEnabled(editable);
    ui->lineEditPais->setEnabled(editable);

    // El ISBN siempre es editable en modo búsqueda
    ui->lineEditIsbn->setEnabled(true);
}

void DialogoLibro::onBuscarClicked()
{
    if (ui->lineEditIsbn->text().isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Ingrese un ISBN para buscar");
        return;
    }
    accept();
}

void DialogoLibro::onLimpiarClicked()
{
    ui->lineEditIsbn->clear();
    ui->lineEditTitulo->clear();
    ui->lineEditAutor->clear();
    ui->lineEditEditorial->clear();
    ui->spinBoxAnio->setValue(2023);
    ui->lineEditPais->clear();
    validarCampos();

}

QString DialogoLibro::getIsbnBusqueda() const
{
    return ui->lineEditIsbn->text().trimmed();
}

Libro DialogoLibro::getLibro() const
{
    return Libro(
        ui->lineEditIsbn->text().trimmed(),
        ui->lineEditTitulo->text().trimmed(),
        ui->lineEditAutor->text().trimmed(),
        ui->lineEditEditorial->text().trimmed(),
        ui->spinBoxAnio->value(),
        ui->lineEditPais->text().trimmed(),
        true
        );
}

void DialogoLibro::accept()
{
    if (m_modo == Buscar && ui->lineEditIsbn->text().isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Ingrese un ISBN para buscar");
        return;
    }

    if (m_modo != Buscar) {
        validarCampos();  // Verifica y marca campos

        if (!ui->btnAceptar->isEnabled()) {
            QMessageBox::warning(this, "Campos incompletos", "Por favor completá todos los campos correctamente.");
            return;
        }
    }

    QDialog::accept();
}



void DialogoLibro::validarCampos()
{
    bool isbnValido = !ui->lineEditIsbn->text().isEmpty() &&
                      ui->lineEditIsbn->text().remove(QRegularExpression("\\D")).length() >= 10;
    resaltarCampo(ui->lineEditIsbn, isbnValido);
    if(!isbnValido){
        QToolTip::showText(ui->lineEditIsbn->mapToGlobal(QPoint(0,ui->lineEditIsbn->height())),
                           "El ISBN debe tener al menos 10 dígitos numéricos");
    }
    bool tituloValido = !ui->lineEditTitulo->text().isEmpty();
    bool autorValido = !ui->lineEditAutor->text().isEmpty();
    bool editorialValido = !ui->lineEditEditorial->text().isEmpty();
    bool paisValido = !ui->lineEditPais->text().isEmpty();
    bool anioValido = ui->spinBoxAnio->value() > 0;

    resaltarCampo(ui->lineEditIsbn, isbnValido);
    resaltarCampo(ui->lineEditTitulo, tituloValido);
    resaltarCampo(ui->lineEditAutor, autorValido);
    resaltarCampo(ui->lineEditEditorial, editorialValido);
    resaltarCampo(ui->lineEditPais, paisValido);

    bool camposCompletos = isbnValido && tituloValido && autorValido && editorialValido && paisValido && anioValido;
    ui->btnAceptar->setEnabled(camposCompletos);
}


void DialogoLibro::resaltarCampo(QLineEdit* campo, bool valido)
{
    if (valido) {
        campo->setStyleSheet(""); // Limpia el estilo
    } else {
        campo->setStyleSheet("border: 2px solid red;");
    }
}


