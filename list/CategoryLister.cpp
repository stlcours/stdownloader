#include <boost/regex.hpp>
#include "Configure.h"
#include "ListCollection.h"
#include "CategoryLister.h"
#include "CategoryListStruct.h"
#include "CategoryListMusicStruct.h"
#include "CategoryCache.h"
#include "Utils.hpp"
#include "Resource.h"

namespace songtaste
{

    CategoryLister::CategoryLister(bool cache)
        : _catlist(nullptr), _http(_io), _cache(cache)
    {
        Configure &config = *(Configure::getInstance());

        _url_category   = config[constant::config::urls][constant::config::category].asString();
        _regex_category = config[constant::config::regexs][constant::config::categorylist].asString();

        if (_url_category.empty() || _regex_category.empty()) {
            throw std::logic_error(constant::error::configure_error);
        }

        std::string user_agent = config[constant::config::useragent].asString();

        setUserAgent(user_agent, &_http);

        _catlist   = new ListCollection;
    }

    CategoryLister::~CategoryLister()
    {
        SAFERELEASE(_catlist);
    }

    ListCollection *
    CategoryLister::getListAt(const unsigned int)
    {
        //load from cache
        ICache *cache = new CategoryCache;
        if (_cache && cache->exsit()) {
            cache->load(_catlist);
            SAFERELEASE(cache);
            return _catlist;
        }
        //no cache
        boost::system::error_code ec;
        //open connection
        _http.open(_url_category, ec);
        if (ec) {
            throw std::logic_error(ec.message());
        }
        std::stringstream ss;
        ss << &_http;
        std::string html = ss.str();

        boost::regex pattern(_regex_category);
        boost::smatch matches;
        std::string::const_iterator s = html.begin();
        std::string::const_iterator e = html.end();

        while (boost::regex_search(s, e, matches, pattern)) {
            auto cls = new CategoryListStruct;
            cls->idx      = matches.str(1);
            cls->catid    = matches.str(2);
            cls->catname  = matches.str(3);
            cls->width    = matches.str(4);
            cls->catnum   = matches.str(5);
            //add to container
            _catlist->add(cls);
            //iterate next matching
            s = matches[5].second;
        }
        //cache
        if (_cache) {
            cache->save(_catlist);
            SAFERELEASE(cache);
        }
        return _catlist;
    }

}
