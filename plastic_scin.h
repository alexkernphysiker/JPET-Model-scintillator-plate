// this file is distributed under 
// MIT license
#ifndef UEGaTsDc
#define UEGaTsDc
#include <RectScin/rectscin.h>
class BC420:public RectangularScintillator{
public:
    BC420(std::vector<Pair>&& dimensions);
    virtual ~BC420();
};
#endif