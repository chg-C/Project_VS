#pragma once

#include "CustomDefine.h"
#include "Singleton.h"

#include <queue>
#include <unordered_map>
#include <algorithm>

using std::unordered_map;

/// <summary>
/// 객체 캐시. delete 필요 객체는 AutoDeleteCache / release 필요 객체는 AutoReleaseCache 사용할 것
/// </summary>
/// <typeparam name="key">검색 key</typeparam>
/// <typeparam name="value">값</typeparam>
template<typename Key, typename Value>
class Cache
{
protected:
	Cache() {}
	virtual ~Cache() { Clear(); }
protected:
	std::unordered_map<Key, Value*> cache;
public:
	/// <summary>
	/// Cache에 값 저장
	/// </summary>
	/// <param name="key">키 값</param>
	/// <param name="value">저장될 값 포인터</param>
	void Put(const Key& key, Value* value)
	{
		if (Exists(key))
		{
			Remove(key);
		}

		cache[key] = value;
	}
	/// <summary>
	/// Cache에 해당 Key로 저장된 값이 있는지 확인
	/// </summary>
	/// <param name="key">키 값</param>
	/// <returns>있으면 true, 없으면 false</returns>
	bool Exists(const Key& key)
	{
		if (cache.find(key) == cache.end())
			return false;
		else
			return true;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	Value* Get(const Key& key)
	{
		auto it = cache.find(key);
		if (it != cache.end())
		{
			return it->second;
		}
		return nullptr;
	}
	/// <summary>
	/// 해당 Key로 저장된 값을 Cache에서 제거. 
	/// 동적 할당된 값이라면 수동으로 제거하거나 AutoDeleteCache 혹은 AutoReleaseCache를 대신 사용할 것.
	/// </summary>
	/// <param name="key">키 값</param>
	/// <returns>삭제 성공시 true</returns>
	virtual bool Remove(const Key& key)
	{
		cache.erase(key);

		return true;
	}
	size_t GetSize() { return cache.size(); }
	virtual void Clear() { cache.clear(); }
};

/// <summary>
/// 객체 캐시, Remove/Clear시 자동 delete 지원
/// </summary>
/// <typeparam name="key">검색 key</typeparam>
/// <typeparam name="value">값</typeparam>
template<typename Key, typename Value>
class AutoDeleteCache : public Cache<Key, Value>, public Singleton<AutoDeleteCache<Key, Value>>
{
	friend class Singleton<AutoDeleteCache<Key, Value>>;
protected:
	AutoDeleteCache() {}
	~AutoDeleteCache() { Clear(); }
public:
	/// <summary>
	/// 해당 Key로 저장된 값을 Cache에서 제거하면서 삭제.
	/// </summary>
	/// <param name="key">키 값</param>
	/// <returns>삭제 성공시 true</returns>
	virtual bool Remove(const Key& key)
	{
		Value* value = Cache<Key, Value>::cache[key];
		SAFE_DELETE(value);
		Cache<Key, Value>::cache.erase(key);

		return true;
	}
	virtual void Clear() {
		for (auto& pair : Cache<Key, Value>::cache)
		{
			SAFE_DELETE(pair.second);
		}
		Cache<Key, Value>::cache.clear();
	}
};

/// <summary>
/// 객체 캐시, Clear시 자동 Release 지원
/// </summary>
/// <typeparam name="key">검색 key</typeparam>
/// <typeparam name="value">값</typeparam>
template<typename Key, typename Value>
class AutoReleaseCache : public Cache<Key, Value>, public Singleton<AutoReleaseCache<Key, Value>>
{
	friend class Singleton<AutoReleaseCache<Key, Value>>;
protected:
	AutoReleaseCache() {}
	~AutoReleaseCache() { Clear(); }
public:
	/// <summary>
	/// 해당 Key로 저장된 값을 Cache에서 제거하면서 해제.
	/// </summary>
	/// <param name="key">키 값</param>
	/// <returns>해제 성공시 true</returns>
	virtual bool Remove(const Key& key) {
		Value* value = Cache<Key, Value>::cache[key];
		SAFE_RELEASE(value);
		Cache<Key, Value>::cache.erase(key);

		return true;
	}
	virtual void Clear() {
		for (auto& pair : Cache<Key, Value>::cache)
		{
			SAFE_RELEASE(pair.second);
		}
		Cache<Key, Value>::cache.clear();
	}
};
