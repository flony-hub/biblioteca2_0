#include "dialogousuario.h"
#include "ui_dialogousuario.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QPainter>

DialogoUsuario::DialogoUsuario(QWidget *parent, Modo modo)
    : QDialog(parent),
    ui(new Ui::DialogoUsuario),
    m_modo(modo),
    m_db(DatabaseManager::getInstance())
{
    ui->setupUi(this);
    configurarInterfaz();
}





DialogoUsuario::~DialogoUsuario()
{
    delete ui;
}

void DialogoUsuario::configurarInterfaz()
{
    switch(m_modo) {
    case Nuevo:
        setWindowTitle("Nuevo Usuario");
        ui->btnBuscar->setVisible(false);
        ui->btnEliminar->setVisible(false);
        break;
    case Editar:
        setWindowTitle("Editar Usuario");
        ui->btnBuscar->setVisible(false);
        ui->lineEditDni->setEnabled(false);
        break;
    case Buscar:
        setWindowTitle("Buscar Usuario");
        ui->btnAceptar->setVisible(false);
        ui->btnEliminar->setVisible(false);
        ui->lineEditNombre->setEnabled(false);
        ui->lineEditEmail->setEnabled(false);
        ui->lineEditTelefono->setEnabled(false);
        break;
    }
}

void DialogoUsuario::paintEvent(QPaintEvent *event)
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

void DialogoUsuario::on_btnAceptar_clicked()
{
    if (!validarCampos()) return;

    guardarDatosUsuario();

    if (m_modo == Nuevo) {
        if (m_db.agregarUsuario(m_usuarioActual)) {
            QMessageBox::information(this, "Éxito", "Usuario agregado correctamente.");
            accept();
        } else {
            QMessageBox::warning(this, "Error", "No se pudo agregar el usuario.");
        }
    } else if (m_modo == Editar) {
        if (m_db.actualizarUsuario(m_usuarioActual)) {
            emit usuarioActualizado();
            QMessageBox::information(this, "Éxito", "Usuario actualizado correctamente.");
            accept();
        } else {
            QMessageBox::warning(this, "Error", "No se pudo actualizar el usuario.");
        }
    }
}

void DialogoUsuario::on_btnBuscar_clicked()
{
    QString dni = ui->lineEditDni->text().trimmed();
    if (dni.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Ingrese un DNI para buscar.");
        return;
    }

    Usuario usuario = m_db.obtenerUsuario(dni);
    if (!usuario.dni().isEmpty()) {
        // usuario encontrado
        m_usuarioActual = usuario;
        cargarDatosUsuario();
    } else {
        QMessageBox::warning(this, "No encontrado", "No se encontró un usuario con ese DNI.");
    }

}

void DialogoUsuario::on_btnActualizar_clicked()
{
    cargarDatosUsuario();
}

void DialogoUsuario::on_btnEliminar_clicked()
{
    QString dni = m_usuarioActual.dni();
    if (QMessageBox::question(this, "Confirmar eliminación",
                              "¿Estás seguro que deseas eliminar este usuario?") == QMessageBox::Yes) {
        if (m_db.eliminarUsuario(dni)) {
            emit usuarioEliminado();
            QMessageBox::information(this, "Eliminado", "Usuario eliminado correctamente.");
            accept();
        } else {
            QMessageBox::warning(this, "Error", "No se pudo eliminar el usuario.");
        }
    }
}




void DialogoUsuario::on_btnCancelar_clicked()
{
    reject();
}

void DialogoUsuario::setUsuario(const Usuario &usuario)
{
    m_usuarioActual = usuario;
    ui->lineEditDni->setText(usuario.dni());
    ui->lineEditNombre->setText(usuario.nombre());
    ui->lineEditTelefono->setText(usuario.telefono());
    ui->lineEditEmail->setText(usuario.email());
}

void DialogoUsuario::cargarDatosUsuario()
{
    setUsuario(m_usuarioActual);
}

void DialogoUsuario::guardarDatosUsuario()
{
    m_usuarioActual.setDni(ui->lineEditDni->text().trimmed());
    m_usuarioActual.setNombre(ui->lineEditNombre->text().trimmed());
    m_usuarioActual.setTelefono(ui->lineEditTelefono->text().trimmed());
    m_usuarioActual.setEmail(ui->lineEditEmail->text().trimmed());
}

bool DialogoUsuario::validarCampos()
{
    if (ui->lineEditDni->text().trimmed().isEmpty() ||
        ui->lineEditNombre->text().trimmed().isEmpty() ||
        ui->lineEditTelefono->text().trimmed().isEmpty() ||
        ui->lineEditEmail->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Todos los campos deben estar completos.");
        return false;
    }

    QRegularExpression emailRegex(R"(^[\w\.-]+@[\w\.-]+\.\w{2,4}$)");
    if (!emailRegex.match(ui->lineEditEmail->text().trimmed()).hasMatch()) {
        QMessageBox::warning(this, "Advertencia", "El email ingresado no es válido.");
        return false;
    }

    return true;
}

void DialogoUsuario::limpiarCampos()
{
    ui->lineEditDni->clear();
    ui->lineEditNombre->clear();
    ui->lineEditTelefono->clear();
    ui->lineEditEmail->clear();
}

void DialogoUsuario::setCamposEditables(bool editable)
{
    ui->lineEditDni->setEnabled(editable);
    ui->lineEditNombre->setEnabled(editable);
    ui->lineEditTelefono->setEnabled(editable);
    ui->lineEditEmail->setEnabled(editable);
}
