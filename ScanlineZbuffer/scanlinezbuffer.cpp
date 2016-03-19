#include "scanlinezbuffer.h"
#include "QFileDialog"
#include "QDir"

ScanlineZbuffer::ScanlineZbuffer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
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
	

}


