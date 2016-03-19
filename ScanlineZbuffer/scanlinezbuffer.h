#ifndef SCANLINEZBUFFER_H
#define SCANLINEZBUFFER_H

#include <QtWidgets/QMainWindow>
#include "ui_scanlinezbuffer.h"

class ScanlineZbuffer : public QMainWindow
{
	Q_OBJECT

public:
	ScanlineZbuffer(QWidget *parent = 0);
	~ScanlineZbuffer();
	void createActions();
	void open();
private:
	Ui::ScanlineZbufferClass ui;
};

#endif // SCANLINEZBUFFER_H
