#pragma once

#include <QtWidgets/QWidget>
#include "ui_XImage.h"

class XImage : public QWidget
{
	Q_OBJECT

public:
	XImage(QWidget *parent = Q_NULLPTR);
	void ViewImage(QImage *img);

public slots://信号槽
	void Open();
	void Deal();

private:
	Ui::XImageClass ui;
	QImage *img = NULL;//存放图片
	QImage imgDeal;//存放用来处理的图片
};
