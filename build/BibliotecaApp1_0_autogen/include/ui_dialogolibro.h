/********************************************************************************
** Form generated from reading UI file 'dialogolibro.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGOLIBRO_H
#define UI_DIALOGOLIBRO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogoLibro
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *labelBuscar;
    QLineEdit *lineEditIsbn;
    QLabel *labelTitulo;
    QLineEdit *lineEditTitulo;
    QLabel *labelAutor;
    QLineEdit *lineEditAutor;
    QLabel *labelEditorial;
    QLineEdit *lineEditEditorial;
    QLabel *labelAnio;
    QSpinBox *spinBoxAnio;
    QLabel *labelPais;
    QLineEdit *lineEditPais;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnBuscar;
    QPushButton *btnLimpiar;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAceptar;
    QPushButton *btnCancelar;

    void setupUi(QDialog *DialogoLibro)
    {
        if (DialogoLibro->objectName().isEmpty())
            DialogoLibro->setObjectName("DialogoLibro");
        DialogoLibro->resize(450, 400);
        verticalLayout = new QVBoxLayout(DialogoLibro);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(DialogoLibro);
        groupBox->setObjectName("groupBox");
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName("formLayout");
        labelBuscar = new QLabel(groupBox);
        labelBuscar->setObjectName("labelBuscar");

        formLayout->setWidget(0, QFormLayout::LabelRole, labelBuscar);

        lineEditIsbn = new QLineEdit(groupBox);
        lineEditIsbn->setObjectName("lineEditIsbn");

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditIsbn);

        labelTitulo = new QLabel(groupBox);
        labelTitulo->setObjectName("labelTitulo");

        formLayout->setWidget(1, QFormLayout::LabelRole, labelTitulo);

        lineEditTitulo = new QLineEdit(groupBox);
        lineEditTitulo->setObjectName("lineEditTitulo");

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditTitulo);

        labelAutor = new QLabel(groupBox);
        labelAutor->setObjectName("labelAutor");

        formLayout->setWidget(2, QFormLayout::LabelRole, labelAutor);

        lineEditAutor = new QLineEdit(groupBox);
        lineEditAutor->setObjectName("lineEditAutor");

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditAutor);

        labelEditorial = new QLabel(groupBox);
        labelEditorial->setObjectName("labelEditorial");

        formLayout->setWidget(3, QFormLayout::LabelRole, labelEditorial);

        lineEditEditorial = new QLineEdit(groupBox);
        lineEditEditorial->setObjectName("lineEditEditorial");

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditEditorial);

        labelAnio = new QLabel(groupBox);
        labelAnio->setObjectName("labelAnio");

        formLayout->setWidget(4, QFormLayout::LabelRole, labelAnio);

        spinBoxAnio = new QSpinBox(groupBox);
        spinBoxAnio->setObjectName("spinBoxAnio");
        spinBoxAnio->setMinimum(0);
        spinBoxAnio->setMaximum(3000);
        spinBoxAnio->setValue(2023);

        formLayout->setWidget(4, QFormLayout::FieldRole, spinBoxAnio);

        labelPais = new QLabel(groupBox);
        labelPais->setObjectName("labelPais");

        formLayout->setWidget(5, QFormLayout::LabelRole, labelPais);

        lineEditPais = new QLineEdit(groupBox);
        lineEditPais->setObjectName("lineEditPais");

        formLayout->setWidget(5, QFormLayout::FieldRole, lineEditPais);


        verticalLayout->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnBuscar = new QPushButton(DialogoLibro);
        btnBuscar->setObjectName("btnBuscar");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnBuscar->setIcon(icon);

        horizontalLayout->addWidget(btnBuscar);

        btnLimpiar = new QPushButton(DialogoLibro);
        btnLimpiar->setObjectName("btnLimpiar");

        horizontalLayout->addWidget(btnLimpiar);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnAceptar = new QPushButton(DialogoLibro);
        btnAceptar->setObjectName("btnAceptar");
        btnAceptar->setEnabled(false);

        horizontalLayout->addWidget(btnAceptar);

        btnCancelar = new QPushButton(DialogoLibro);
        btnCancelar->setObjectName("btnCancelar");

        horizontalLayout->addWidget(btnCancelar);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DialogoLibro);
        QObject::connect(btnCancelar, &QPushButton::clicked, DialogoLibro, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(DialogoLibro);
    } // setupUi

    void retranslateUi(QDialog *DialogoLibro)
    {
        DialogoLibro->setWindowTitle(QCoreApplication::translate("DialogoLibro", "Gesti\303\263n de Libro", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DialogoLibro", "Datos del Libro", nullptr));
        labelBuscar->setText(QCoreApplication::translate("DialogoLibro", "Buscar por ISBN:", nullptr));
        lineEditIsbn->setPlaceholderText(QCoreApplication::translate("DialogoLibro", "Ingrese ISBN a buscar", nullptr));
        labelTitulo->setText(QCoreApplication::translate("DialogoLibro", "T\303\255tulo:", nullptr));
        labelAutor->setText(QCoreApplication::translate("DialogoLibro", "Autor:", nullptr));
        labelEditorial->setText(QCoreApplication::translate("DialogoLibro", "Editorial:", nullptr));
        labelAnio->setText(QCoreApplication::translate("DialogoLibro", "A\303\261o:", nullptr));
        labelPais->setText(QCoreApplication::translate("DialogoLibro", "Pa\303\255s:", nullptr));
        btnBuscar->setText(QCoreApplication::translate("DialogoLibro", "Buscar", nullptr));
        btnLimpiar->setText(QCoreApplication::translate("DialogoLibro", "Limpiar", nullptr));
        btnAceptar->setText(QCoreApplication::translate("DialogoLibro", "Aceptar", nullptr));
        btnCancelar->setText(QCoreApplication::translate("DialogoLibro", "Cancelar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogoLibro: public Ui_DialogoLibro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGOLIBRO_H
