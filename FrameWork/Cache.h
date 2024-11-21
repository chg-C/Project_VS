#pragma once

#include "CustomDefine.h"
#include "Singleton.h"

#include <queue>
#include <unordered_map>
#include <algorithm>

using std::unordered_map;

/// <summary>
/// ��ü ĳ��. delete �ʿ� ��ü�� AutoDeleteCache / release �ʿ� ��ü�� AutoReleaseCache ����� ��
/// </summary>
/// <typeparam name="key">�˻� key</typeparam>
/// <typeparam name="value">��</typeparam>
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
	/// Cache�� �� ����
	/// </summary>
	/// <param name="key">Ű ��</param>
	/// <param name="value">����� �� ������</param>
	void Put(const Key& key, Value* value)
	{
		if (Exists(key))
		{
			Remove(key);
		}

		cache[key] = value;
	}
	/// <summary>
	/// Cache�� �ش� Key�� ����� ���� �ִ��� Ȯ��
	/// </summary>
	/// <param name="key">Ű ��</param>
	/// <returns>������ true, ������ false</returns>
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
	/// �ش� Key�� ����� ���� Cache���� ����. 
	/// ���� �Ҵ�� ���̶�� �������� �����ϰų� AutoDeleteCache Ȥ�� AutoReleaseCache�� ��� ����� ��.
	/// </summary>
	/// <param name="key">Ű ��</param>
	/// <returns>���� ������ true</returns>
	virtual bool Remove(const Key& key)
	{
		cache.erase(key);

		return true;
	}
	size_t GetSize() { return cache.size(); }
	virtual void Clear() { cache.clear(); }
};

/// <summary>
/// ��ü ĳ��, Remove/Clear�� �ڵ� delete ����
/// </summary>
/// <typeparam name="key">�˻� key</typeparam>
/// <typeparam name="value">��</typeparam>
template<typename Key, typename Value>
class AutoDeleteCache : public Cache<Key, Value>, public Singleton<AutoDeleteCache<Key, Value>>
{
	friend class Singleton<AutoDeleteCache<Key, Value>>;
protected:
	AutoDeleteCache() {}
	~AutoDeleteCache() { Clear(); }
public:
	/// <summary>
	/// �ش� Key�� ����� ���� Cache���� �����ϸ鼭 ����.
	/// </summary>
	/// <param name="key">Ű ��</param>
	/// <returns>���� ������ true</returns>
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
/// ��ü ĳ��, Clear�� �ڵ� Release ����
/// </summary>
/// <typeparam name="key">�˻� key</typeparam>
/// <typeparam name="value">��</typeparam>
template<typename Key, typename Value>
class AutoReleaseCache : public Cache<Key, Value>, public Singleton<AutoReleaseCache<Key, Value>>
{
	friend class Singleton<AutoReleaseCache<Key, Value>>;
protected:
	AutoReleaseCache() {}
	~AutoReleaseCache() { Clear(); }
public:
	/// <summary>
	/// �ش� Key�� ����� ���� Cache���� �����ϸ鼭 ����.
	/// </summary>
	/// <param name="key">Ű ��</param>
	/// <returns>���� ������ true</returns>
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
