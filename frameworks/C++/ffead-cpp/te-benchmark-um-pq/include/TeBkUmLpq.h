/*
	Copyright 2009-2020, Sumeet Chhetri

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
/*
 * TeBkUmLpq.h
 *
 *  Created on: 03-Feb-2020
 *      Author: sumeetc
 */

#ifndef WEB_TE_BENCHMARK_UM_INCLUDE_TeBkUmLpq_H_
#define WEB_TE_BENCHMARK_UM_INCLUDE_TeBkUmLpq_H_
#include "TemplateHandler.h"
#include "vector"
#ifndef OS_MINGW
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include "DataSourceManager.h"
#include <stdlib.h>
#include <algorithm>
#include "CryptoHandler.h"
#include "vector"
#include "CastUtil.h"
#include <stdlib.h>
#include "CacheManager.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "JSONSerialize.h"
#include "string"
#include "yuarel.h"
#include "Router.h"

typedef void (*TeBkUmLpqTemplatePtr) (Context*, std::string&);

class TeBkUmLpqWorld {
	int id;
	int randomNumber;
public:
	TeBkUmLpqWorld();
	virtual ~TeBkUmLpqWorld();
	int getId() const;
	void setId(int id);
	int getRandomNumber() const;
	void setRandomNumber(int randomNumber);
};

class TeBkUmLpqFortune {
	int id;
	std::string message;
public:
	TeBkUmLpqFortune();
	virtual ~TeBkUmLpqFortune();
	int getId() const;
	void setId(int id);
	const std::string& getMessage() const;
	void setMessage(const std::string& message);
	bool operator < (const TeBkUmLpqFortune& other) const;
};

class TeBkUmLpqMessage {
	std::string message;
public:
	virtual ~TeBkUmLpqMessage();
	const std::string& getMessage() const;
	void setMessage(const std::string& message);
};

class TeBkUmLpqRouter : public Router {
	static const std::string HELLO_WORLD;
	static std::string WORLD;
	static std::string WORLD_ONE_QUERY;
	static std::string WORLD_ALL_QUERY;
	static std::string FORTUNE_ALL_QUERY;
	bool strToNum(const char* str, int len, int& ret);

	void db(TeBkUmLpqWorld&);
	void queries(const char*, int, std::vector<TeBkUmLpqWorld>&);
	static void dbUtil(void* ctx, int rn, std::vector<LibpqRes>& data);

	void updates(const char*, int, std::vector<TeBkUmLpqWorld>&);
	static void updatesUtil(void* ctx, int rn, std::vector<LibpqRes>& data);
	
	void cachedWorlds(const char*, int, std::vector<TeBkUmLpqWorld>&);
	static void updateCacheUtil(void* ctx, int rn, std::vector<LibpqRes>& data);

	void getContext(HttpRequest* request, Context* context);
	static void getContextUtil(void* ctx, int rn, std::vector<LibpqRes>& data);
public:
	void updateCache();
	void route(HttpRequest* req, HttpResponse* res, void* dlib, void* ddlib);
};

#endif /* WEB_TE_BENCHMARK_UM_INCLUDE_TeBkUmLpq_H_ */
