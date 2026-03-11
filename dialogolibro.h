#ifndef DIALOGOLIBRO_H
#define DIALOGOLIBRO_H

#include <QDialog>
#include <QLineEdit>
#include "libro.h"

namespace Ui {
class DialogoLibro;
}


class DialogoLibro : public QDialog
{
    Q_OBJECT

public:
    enum Modo { Nuevo, Editar, Buscar };

    explicit DialogoLibro(QWidget *parent = nullptr, Modo modo = Nuevo, const Libro* libroExistente = nullptr);
    ~DialogoLibro();


    QString getIsbnBusqueda() const;
    Libro getLibro() const;
    void accept() override;
    void resaltarCampo(QLineEdit* campo, bool valido);


private slots:
    void onBuscarClicked();
    void onLimpiarClicked();

protected:
    void paintEvent(QPaintEvent *event) override;
    
private:
    void configurarModoBusqueda();
    void configurarModoEdicion(const Libro* libro);
    void configurarModoNuevo();
    void setCamposEditables(bool editable);
    void validarCampos();
    Ui::DialogoLibro *ui;
    Modo m_modo;
};


#endif // DIALOGOLIBRO_H
