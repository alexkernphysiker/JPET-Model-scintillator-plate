#ifndef UEGaTsDc
#define UEGaTsDc
#include <rectscin.h>
#define static_left(A) (static_cast<decltype(A)&&>(A))
class BC420:public RectangularScintillator{
public:
    BC420(std::vector<Pair>&& dimensions);
    virtual ~BC420();
};
#endif