// this file is distributed under 
// MIT license
#ifndef UEGaTsDc
#define UEGaTsDc
#include <RectScin/scintillator.h>
namespace Model{
	using namespace std;
	using namespace RectangularScintillator;
	class BC420:public Scintillator{
	public:
		BC420(const vector<Pair>& dimensions);
		BC420(vector<Pair>&&dimensions);
		virtual ~BC420();
	};
};
#endif