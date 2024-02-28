#pragma once

template<typename ID>
class IManageable
{
protected:
	ID id;
	bool toRemove;

public:
	void SetID(const ID& _id)
	{
		id = _id;
	}

	ID GetID()const
	{
		return id;
	}
	void SetToRemove(const bool _status)
	{
		toRemove = _status;
	}
	bool IsToRemove() const
	{
		return toRemove;
	}

public:
	IManageable(const ID& _id)
	{
		id = _id;
		toRemove = false;
	}
public:
	virtual void Register() = 0;
};
