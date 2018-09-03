#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windingviewer.h"
#include "windingflatviewer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
// back view
    WindingViewer* wvb=new WindingViewer;
    wvb->setView(WindingViewer::TypeView::backView);
// from UI to winding calculator
    connect(ui->SlotCountEdit,SIGNAL(valueChanged(int)),wvb,SLOT(setSlotCount(int)));
    connect(ui->PoleCountEdit,SIGNAL(valueChanged(int)),wvb,SLOT(setPoleCount(int)));
    connect(ui->WindingTypeSelector,SIGNAL(currentIndexChanged(int)),wvb,SLOT(setWindingType(int)));
    wvb->setSlotCount(48);
    ui->horizontalLayout_3->insertWidget(0,wvb);
// front view
    WindingViewer* wvf=new WindingViewer;
    wvf->setView(WindingViewer::TypeView::frontView);
    // from UI to winding calculator
    connect(ui->SlotCountEdit,SIGNAL(valueChanged(int)),wvf,SLOT(setSlotCount(int)));
    connect(ui->PoleCountEdit,SIGNAL(valueChanged(int)),wvf,SLOT(setPoleCount(int)));
    connect(ui->WindingTypeSelector,SIGNAL(currentIndexChanged(int)),wvf,SLOT(setWindingType(int)));
    wvf->setSlotCount(48);
    ui->horizontalLayout_3->insertWidget(0,wvf);
// slot view
    WindingFlatViewer* wfv=new WindingFlatViewer;
    connect(ui->SlotCountEdit,SIGNAL(valueChanged(int)),wfv,SLOT(setSlotCount(int)));
    connect(ui->PoleCountEdit,SIGNAL(valueChanged(int)),wfv,SLOT(setPoleCount(int)));
    connect(ui->WindingTypeSelector,SIGNAL(currentIndexChanged(int)),wfv,SLOT(setWindingType(int)));
    connect(ui->CoilTypeSelector,SIGNAL(currentIndexChanged(int)),wfv,SLOT(setCoilType(int)));
    wfv->setSlotCount(48);
    ui->horizontalLayout_5->insertWidget(0,wfv);
}

MainWindow::~MainWindow()
{
    delete ui;
}
