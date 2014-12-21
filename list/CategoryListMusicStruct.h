//
// CategoryListMusicStruct.h
// ~~~~~~~~~~
//
// Distributed under the GPLv2 License
//

#ifndef CATEGORYLISTMUSICSTRUCT_H
#define CATEGORYLISTMUSICSTRUCT_H

#include "IListStruct.h"

namespace songtaste {
    class CategoryListMusicStruct : public IListStruct {
    public:
        explicit CategoryListMusicStruct();
        ~CategoryListMusicStruct();
        
        string songid;
        string songname;
        string recnum;
    private:
        
    };  
}

#endif // CATEGORYLISTMUSICSTRUCT_H