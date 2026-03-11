#ifndef DIALOGOUSUARIO_H
#define DIALOGOUSUARIO_H

#include <QRegularExpression>
#include <QPushButton>
#include "databasemanager.h"
#include "usuario.h"
#include <QDialog>


namespace Ui {
    class DialogoUsuario;
    }

class DialogoUsuario : public QDialog
{
    Q_OBJECT
public:
    enum Modo { Nuevo, Editar, Buscar };
    explicit DialogoUsuario(QWidget *parent = nullptr, Modo modo = Nuevo);
    ~DialogoUsuario();
    Usuario usuario() const;
    void setUsuario(const Usuario &usuario);
    void cargarDatosUsuario();
    void guardarDatosUsuario();
    bool validarCampos();
    void limpiarCampos();
    void setCamposEditables(bool);

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_btnAceptar_clicked();
    void on_btnBuscar_clicked();
    void on_btnActualizar_clicked();
    void on_btnEliminar_clicked();
    void on_btnCancelar_clicked();


signals:
    void usuarioActualizado();
    void usuarioEliminado();


private:
    Ui::DialogoUsuario *ui;
    Modo m_modo;
    Usuario m_usuarioActual;
    DatabaseManager &m_db;
    void configurarInterfaz();
    bool validarFormulario();

};

#endif // DIALOGOUSUARIO_H
