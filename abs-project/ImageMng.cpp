#include"DxLib.h"
#include "ImageMng.h"


ImageMng *ImageMng::s_Instance = nullptr;

void ImageMng::Create(void)
{
	if (!s_Instance)
	{
		s_Instance = new ImageMng();
	}
}

void ImageMng::Destroy(void)
{
	if (s_Instance)
	{
		delete s_Instance;
	}
	s_Instance = nullptr;
}
 //imageMap[f_name(ここはkeyを書く)][]
const VEC_INT & ImageMng::GetID(std::string f_name)
{

     	if (imgMap.find(f_name) == imgMap.end())					//f_nameの画像ハンドルがあるか    find（見つける）
	{
		imgMap[f_name].resize(1);
		imgMap[f_name][0] = LoadGraph(f_name.c_str());
	}
	return imgMap[f_name];
}

const VEC_INT & ImageMng::GetID(std::string f_name, VECTOR divsize, VECTOR divCnt, VECTOR chipOffset)
{
	if (imgMap.find(f_name) == imgMap.end())
	{
		imgMap[f_name].resize(divCnt.x*divCnt.y);
		LoadDivGraph(f_name.c_str(),
						divCnt.x*divCnt.y,divCnt.x, divCnt.y,
						divsize.x, divsize.y, &imgMap[f_name][0]);
	}
	return imgMap[f_name];
}

ImageMng::ImageMng()
{
}


ImageMng::~ImageMng()
{
}
