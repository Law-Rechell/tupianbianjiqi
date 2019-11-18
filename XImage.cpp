#include "XImage.h"
#include"ImageThread.h"
#include<QFileDialog>
#include<QTime>

XImage::XImage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

//缩放图片并显示
void XImage::ViewImage(QImage *img)
{
	QImage simg;//缩放图片
	if (img->width() > img->height())
	{
		simg = img->scaledToWidth(ui.view->width());
	}
	else
	{
		simg = img->scaledToHeight(ui.view->height());
	}
	ui.view->setPixmap(QPixmap::fromImage(simg));//设置图片显示
}

//打开图片
void  XImage::Open()
{
	QString filename = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择图片"));
	if (filename.isEmpty()) return;
	if (!img)
	{
		delete img;
		img = NULL;
	}
	img = new QImage(filename);
	if (!img) return;

	ViewImage(img);
}

//处理函数，调节亮度
void XImage::Deal()
{
	float b = (float)ui.bright->value()/100;//获取亮度值
	int thread = ui.thread->value();
	if (!img) return;
	imgDeal = img->copy();

	unsigned char *data = imgDeal.bits();
	int pixCount = img->width()*img->height();//像素数量
	QTime t;
	t.start();
	ImageThread::DealImage(data, pixCount, b, thread);
	for (;;)
	{
		int percent = ImageThread::DealPercent();
		ui.progress->setValue(percent);
		if (percent >= 100) break;
	}
	ImageThread::Wait();
	int ms = t.elapsed();
	char buf[128] = { 0 };
	sprintf(buf, "%d毫秒", ms);
	ui.dealtime->setText(QString::fromLocal8Bit(buf));
	//QThread::msleep(1000);
	/*for (int i = 0; i < pixCount; i++)
	{
		int B = data[i * 4]*b;
		int G = data[i * 4 + 1]*b;
		int R = data[i * 4 + 2]*b;
		if (B > 255) B = 255;
		if (G > 255) G = 255;
		if (R > 255) R = 255;
		data[i * 4] = B;
		data[i * 4 + 1] = G;
		data[i * 4 + 2] = R;
	}*/

	ViewImage(&imgDeal);
}