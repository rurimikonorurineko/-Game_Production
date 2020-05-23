#pragma once
#include "DxLib.h"
#include <map>
#include<vector>

#define IMAGE_ID(X) (ImageMng::GetInstance().GetID(X));// ベタで書いたらできた→IMAGE_ID がおかしい
using VEC_INT = std::vector<int>;

class ImageMng
{
public:
	static void Create(void);
	static void Destroy(void);
	static ImageMng &GetInstance(void)
	{
		Create();
		return *s_Instance;
	}
	const VEC_INT& GetID(std::string f_name);
	const VEC_INT& GetID(std::string f_name, VECTOR divsize, VECTOR divCnt, VECTOR chipOffset);
private:
	ImageMng();
	~ImageMng();
	static ImageMng *s_Instance;

	// std::map<キーの型,連想配列の型>連想配列名;
	std::map<std::string, VEC_INT>imgMap;
};

