#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

#include "QVTKOpenGLNativeWidget.h"

MainWindow::~MainWindow()
{
    QVTKOpenGLNativeWidget* vtkWidget = new QVTKOpenGLNativeWidget(this);
    this->setCentralWidget(vtkWidget);

//    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
//    vtkWidget->setRenderWindow(renderWindow);

//    vtkNew<vtkRenderer> renderer;
//    renderWindow->AddRenderer(renderer);

    delete ui;
}

