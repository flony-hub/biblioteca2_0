/********************************************************************************
** Form generated from reading UI file 'dialogousuario.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGOUSUARIO_H
#define UI_DIALOGOUSUARIO_H

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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogoUsuario
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEditDni;
    QLabel *label_2;
    QLineEdit *lineEditNombre;
    QLabel *label_3;
    QLineEdit *lineEditEmail;
    QLabel *label_4;
    QLineEdit *lineEditTelefono;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnBuscar;
    QPushButton *btnActualizar;
    QPushButton *btnEliminar;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAceptar;
    QPushButton *btnCancelar;

    void setupUi(QDialog *DialogoUsuario)
    {
        if (DialogoUsuario->objectName().isEmpty())
            DialogoUsuario->setObjectName("DialogoUsuario");
        DialogoUsuario->resize(506, 400);
        verticalLayout = new QVBoxLayout(DialogoUsuario);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(DialogoUsuario);
        groupBox->setObjectName("groupBox");
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName("formLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEditDni = new QLineEdit(groupBox);
        lineEditDni->setObjectName("lineEditDni");
        lineEditDni->setMaxLength(8);

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditDni);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEditNombre = new QLineEdit(groupBox);
        lineEditNombre->setObjectName("lineEditNombre");

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditNombre);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        lineEditEmail = new QLineEdit(groupBox);
        lineEditEmail->setObjectName("lineEditEmail");

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditEmail);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        lineEditTelefono = new QLineEdit(groupBox);
        lineEditTelefono->setObjectName("lineEditTelefono");
        lineEditTelefono->setMaxLength(15);

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditTelefono);


        verticalLayout->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnBuscar = new QPushButton(DialogoUsuario);
        btnBuscar->setObjectName("btnBuscar");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnBuscar->setIcon(icon);

        horizontalLayout->addWidget(btnBuscar);

        btnActualizar = new QPushButton(DialogoUsuario);
        btnActualizar->setObjectName("btnActualizar");

        horizontalLayout->addWidget(btnActualizar);

        btnEliminar = new QPushButton(DialogoUsuario);
        btnEliminar->setObjectName("btnEliminar");

        horizontalLayout->addWidget(btnEliminar);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnAceptar = new QPushButton(DialogoUsuario);
        btnAceptar->setObjectName("btnAceptar");

        horizontalLayout->addWidget(btnAceptar);

        btnCancelar = new QPushButton(DialogoUsuario);
        btnCancelar->setObjectName("btnCancelar");

        horizontalLayout->addWidget(btnCancelar);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DialogoUsuario);
        QObject::connect(btnAceptar, &QPushButton::clicked, DialogoUsuario, qOverload<>(&QDialog::accept));
        QObject::connect(btnCancelar, &QPushButton::clicked, DialogoUsuario, qOverload<>(&QDialog::reject));

        btnAceptar->setDefault(true);


        QMetaObject::connectSlotsByName(DialogoUsuario);
    } // setupUi

    void retranslateUi(QDialog *DialogoUsuario)
    {
        DialogoUsuario->setWindowTitle(QCoreApplication::translate("DialogoUsuario", "Usuario", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DialogoUsuario", "Datos del Usuario", nullptr));
        label->setText(QCoreApplication::translate("DialogoUsuario", "DNI:", nullptr));
        label_2->setText(QCoreApplication::translate("DialogoUsuario", "Nombre:", nullptr));
        label_3->setText(QCoreApplication::translate("DialogoUsuario", "Email:", nullptr));
        label_4->setText(QCoreApplication::translate("DialogoUsuario", "Tel\303\251fono:", nullptr));
        btnBuscar->setText(QCoreApplication::translate("DialogoUsuario", "&Buscar", nullptr));
        btnActualizar->setText(QCoreApplication::translate("DialogoUsuario", "&Actualizar", nullptr));
        btnEliminar->setText(QCoreApplication::translate("DialogoUsuario", "&Eliminar", nullptr));
        btnAceptar->setText(QCoreApplication::translate("DialogoUsuario", "&Aceptar", nullptr));
        btnCancelar->setText(QCoreApplication::translate("DialogoUsuario", "&Cancelar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogoUsuario: public Ui_DialogoUsuario {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGOUSUARIO_H
