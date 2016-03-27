// this file is distributed under 
// MIT license
#ifndef UEGaTsDc
#define UEGaTsDc
#include <RectScin/scintillator.h>
namespace Model{
	class BC420:public RectangularScintillator::Scintillator{
	public:
		BC420(const std::vector<RectangularScintillator::Pair>& dimensions);
		BC420(const std::vector<RectangularScintillator::Pair>&&dimensions);
		virtual ~BC420();
	};
};
#endif