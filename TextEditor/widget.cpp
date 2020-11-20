#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

#include <QIcon>

#include <QToolBar>

#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include <QFontDialog>
#include <QColorDialog>

#include <QMessageBox>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QIcon WindowIcon = QIcon::fromTheme("window-icon", QIcon("C:/Users/Orange/Documents/QTProjects/TextEditor_2_0/resources/Icon.png"));

    Widget::setWindowIcon(WindowIcon);

    QIcon SaveFileIcon = QIcon::fromTheme("save-file", QIcon("C:/Users/Orange/Documents/QTProjects/TextEditor_2_0/resources/SaveFile.png"));
    QIcon OpenFileIcon = QIcon::fromTheme("open-file", QIcon("C:/Users/Orange/Documents/QTProjects/TextEditor_2_0/resources/OpenFile.png"));
    QIcon CopyIcon = QIcon::fromTheme("copy", QIcon("C:/Users/Orange/Documents/QTProjects/TextEditor_2_0/resources/Copy.png"));
    QIcon CutIcon = QIcon::fromTheme("cut", QIcon("C:/Users/Orange/Documents/QTProjects/TextEditor_2_0/resources/Cut.jpg"));
    QIcon PasteIcon = QIcon::fromTheme("paste", QIcon("C:/Users/Orange/Documents/QTProjects/TextEditor_2_0/resources/Paste.png"));
    QIcon UndoIcon = QIcon::fromTheme("undo", QIcon("C:/Users/Orange/Documents/QTProjects/TextEditor_2_0/resources/Undo.png"));
    QIcon RedoIcon = QIcon::fromTheme("redo", QIcon("C:/Users/Orange/Documents/QTProjects/TextEditor_2_0/resources/Redo.png"));
    QIcon EditTextColorIcon = QIcon::fromTheme("undo", QIcon("C:/Users/Orange/Documents/QTProjects/TextEditor_2_0/resources/EditTextColor.png"));
    QIcon EditBackgroundTextColorIcon = QIcon::fromTheme("undo", QIcon("C:/Users/Orange/Documents/QTProjects/TextEditor_2_0/resources/EditBackgroundTextColor.png"));
    QIcon EditTextFontIcon = QIcon::fromTheme("undo", QIcon("C:/Users/Orange/Documents/QTProjects/TextEditor_2_0/resources/EditTExtFont.png"));
    QIcon AboutQTIcon = QIcon::fromTheme("undo", QIcon("C:/Users/Orange/Documents/QTProjects/TextEditor_2_0/resources/AboutQT.png"));
    QIcon ExitIcon = QIcon::fromTheme("exit", QIcon("C:/Users/Orange/Documents/QTProjects/TextEditor_2_0/resources/ExitIcon.png"));

    QToolBar *Bar = new QToolBar(this);

    QMenuBar *M = new QMenuBar(this);
    QHBoxLayout HeadArea;

    QMenu *FileMenu = new QMenu("File", this);
    QMenu *EditMenu = new QMenu("Edit", this);
    QMenu *ViewMenu = new QMenu("View", this);
    QMenu *AboutMenu = new QMenu("About", this);

    QAction *OpenFileAction = new QAction(OpenFileIcon, "Open file", this);
    QAction *SaveFileAction = new QAction(SaveFileIcon, "Save file", this);
    QAction *ExitAction = new QAction(ExitIcon, "Exit", this);
    QAction *CopyAction = new QAction(CopyIcon, "Copy", this);
    QAction *PasteAction = new QAction(PasteIcon, "Paste", this);
    QAction *CutAction = new QAction(CutIcon, "Cut", this);
    QAction *UndoAction = new QAction(UndoIcon, "Undo", this);
    QAction *RedoAction = new QAction(RedoIcon, "Redo", this);
    QAction *EditTextSizeAction = new QAction(EditTextFontIcon, "Edit text size", this);
    QAction *EditTextColorAction = new QAction(EditTextColorIcon, "Edit text color", this);
    QAction *EditBackgroundTextColorAction = new QAction(EditBackgroundTextColorIcon, "Edit background text color", this);

    QAction *AboutQtAction = new QAction(AboutQTIcon, "About Qt", this);

    FileMenu->addAction(OpenFileAction);
    FileMenu->addAction(SaveFileAction);
    FileMenu->addAction(ExitAction);

    EditMenu->addAction(CopyAction);
    EditMenu->addAction(PasteAction);
    EditMenu->addAction(CutAction);
    EditMenu->addAction(UndoAction);
    EditMenu->addAction(RedoAction);

    ViewMenu->addAction(EditTextColorAction);
    ViewMenu->addAction(EditBackgroundTextColorAction);
    ViewMenu->addAction(EditTextSizeAction);

    AboutMenu->addAction(AboutQtAction);

    M->addMenu(FileMenu);
    M->addMenu(EditMenu);
    M->addMenu(ViewMenu);
    M->addMenu(AboutMenu);

    M->adjustSize();

    Bar->addAction(OpenFileAction);
    Bar->addAction(SaveFileAction);
    Bar->addSeparator();
    Bar->addAction(CopyAction);
    Bar->addAction(PasteAction);
    Bar->addAction(CutAction);
    Bar->addAction(UndoAction);
    Bar->addAction(RedoAction);
    Bar->addSeparator();
    Bar->addAction(EditTextColorAction);
    Bar->addAction(EditBackgroundTextColorAction);
    Bar->addAction(EditTextSizeAction);
    Bar->addSeparator();
    Bar->addAction(AboutQtAction);
    Bar->addSeparator();
    Bar->addAction(ExitAction);

    Bar->move(0, 25);
    Bar->adjustSize();

    connect(ExitAction, &QAction::triggered, [=](){
        QApplication::exit();
    });

    connect(AboutQtAction, &QAction::triggered, [=](){
        QApplication::aboutQt();
    });

    connect(EditTextSizeAction, &QAction::triggered, [=](){
        if (ui->TextEdit->textCursor().hasSelection()){
            bool ok;
            QFont TFDialog = QFontDialog::getFont(&ok, this);

            if (ok)
                ui->TextEdit->setCurrentFont(TFDialog);
        }
        else
            QMessageBox::critical(this, "Error", "You need to select text!", QMessageBox::Ok);
    });

    connect(EditTextColorAction, &QAction::triggered, [=](){
        if (ui->TextEdit->textCursor().hasSelection()){
            QColor TCDialog = QColorDialog::getColor(Qt::black, this, "Choose new text color");

            ui->TextEdit->setTextColor(TCDialog);
        }
        else
            QMessageBox::critical(this, "Error", "You need to select text!", QMessageBox::Ok);
    });

    connect(EditBackgroundTextColorAction, &QAction::triggered, ([=](){
        if (ui->TextEdit->textCursor().hasSelection()){
            QColor BGTCDialog = QColorDialog::getColor(Qt::white, this, "Choose new background text color");

            ui->TextEdit->setTextBackgroundColor(BGTCDialog);
        }
        else
            QMessageBox::critical(this, "Error", "You need to select text!", QMessageBox::Ok);
    }));

    connect(CopyAction, &QAction::triggered, [=](){
        ui->TextEdit->copy();
    });

    connect(PasteAction, &QAction::triggered, [=](){
        ui->TextEdit->paste();
    });

    connect(CutAction, &QAction::triggered, [=](){
        ui->TextEdit->cut();
    });

    connect(UndoAction, &QAction::triggered, [=](){
        ui->TextEdit->undo();
    });

    connect(RedoAction, &QAction::triggered, [=](){
        ui->TextEdit->redo();
    });

    connect(OpenFileAction, &QAction::triggered, [=](){
        QString TextContent;
        QString FileDestination = QFileDialog::getOpenFileName(this, "Open file");

        qDebug() << FileDestination;

        if (FileDestination.isEmpty())
            return;

        QFile file(FileDestination);

        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&file);
        QString line = in.readLine();

        while (!line.isNull()){
            TextContent.append(line);
            TextContent.append("\n");
            line = in.readLine();
        }
        ui->TextEdit->clear();
        ui->TextEdit->setPlainText(TextContent);

        file.close();
        qDebug() << TextContent;
    });

    connect(SaveFileAction, &QAction::triggered, [=](){
        QString FileDestination = QFileDialog::getSaveFileName(this, "Save file");

        qDebug() << FileDestination;

        if (FileDestination.isEmpty())
            return;

        QFile file(FileDestination);

        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&file);
        out << ui->TextEdit->toPlainText() << "\n";
        ui->TextEdit->clear();

        file.close();
    });
}
Widget::~Widget()
{
    delete ui;
}

