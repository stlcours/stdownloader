#include <iostream>
#include "AlbumLister.h"
#include "RecommendLister.h"

using namespace std;
using namespace songtaste;

int main(int argc, char *argv[]) {

    try {
        Lister lister(new RecommendLister);
        ListCollection data = lister->getListAt(2);

        ListCollection::const_iterator it = data.cbegin();
        for (; it != data.end(); ++it) {
            ListStruct ls = *it;

            cout << ls->songname << "\n" << ls->songid << "\n" << ls->uname << "\n"
                << ls->uid << "\n" << ls->uicon << "\n" << ls->recwidth << "\n"
                << ls->rateuid << "\n" << ls->ratedt << "\n" << ls->rateuname;
            cout << endl;
            cout << endl;
        }

    } catch (const logic_error &err) {
        cout << err.what() << endl;
    }

    return 0;
}
