#ifndef SCANLINEZBUFFERVIEW_H
#define SCANLINEZBUFFERVIEW_H

#include <QGraphicsView>
#include "Zbuffer.h"

class ScanlineZbufferView : public QGraphicsView
{ 
	Q_OBJECT


public:
	ScanlineZbufferView(QWidget *parent = 0);
    ~ScanlineZbufferView();

private:
    
};

#endif // SCANLINEZBUFFERVIEW_H
