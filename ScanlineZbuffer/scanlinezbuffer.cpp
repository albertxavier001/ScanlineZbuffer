#include "scanlinezbuffer.h"
#include "QFileDialog"
#include "QDir"

ScanlineZbuffer::ScanlineZbuffer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	createActions();
}

ScanlineZbuffer::~ScanlineZbuffer()
{

}


void ScanlineZbuffer::createActions(){
	QObject::connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(open()));

}

void ScanlineZbuffer::open(){
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open File"), QDir::currentPath());

	zbuffer.scene.loadScene(fileName.toStdString());
	ui.szView->image = zbuffer.ScanlineZbuffer(zbuffer.scene, 0.f, 0.f, 1.f);
	ui.szView->displayImage();
}


