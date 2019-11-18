#include "ImageThread.h"
#include<vector>
using namespace std;
static vector<ImageThread*> threads;

void ImageThread::run()
{
	if (!img) return;
	for (int i = begin; i <= end; i++)
	{
		int B = img[i * 4] * bright;
		int G = img[i * 4 + 1] * bright;
		int R = img[i * 4 + 2] * bright;
		if (B > 255) B = 255;
		if (G > 255) G = 255;
		if (R > 255) R = 255;
		img[i * 4] = B;
		img[i * 4 + 1] = G;
		img[i * 4 + 2] = R;
		cur = i;
	}
}

void ImageThread::DealImage(unsigned char* img, unsigned int size, float bright,int threadCount)
{
	for (int i = 0; i < threads.size(); i++)
	{
		threads[i]->wait();
		delete threads[i];
	}
	threads.clear();

	int tsize = size / threadCount;
	for (int i = 0; i < threadCount; i++)
	{
		ImageThread *th = new ImageThread();
		th->begin = i * tsize;
		th->end = th->begin + tsize;
		th->img = img;
		th->bright = bright;
		if (i == threadCount - 1)
		{
			th->end = size - 1;
		}
		threads.push_back(th);
	}
	for (int i = 0; i < threads.size(); i++)
	{
		threads[i]->start();
	}
}

int ImageThread::DealPercent()
{
	int cur = 0;
	int total = 0;
	for (int i = 0; i < threads.size(); i++)
	{
		cur += threads[i]->cur - threads[i]->begin;
		total += threads[i]->end - threads[i]->begin;
	}
	if (total == 0)	return 0;
	int per = cur * 100 / total;
	return per;
}

void ImageThread::Wait()
{
	for (int i = 0; i < threads.size(); i++)
	{
		threads[i]->wait();
	}
}

ImageThread::ImageThread()
{
}

ImageThread::~ImageThread()
{
}
