#pragma once
#include "UiData.h"
#include "IManager.h"
#include "Singleton.h"
#include <iostream>

using namespace std;

class UiManager : public Singleton<UiManager>, public IManager<string,UiData>
{
public:
	vector<UiData*> GetAllInteractiveUi() const
	{
		vector<UiData*> _interactiveUi;
		for (UiData* _uiData : GetAllValues())
		{
			if (_uiData->IsInteractiveUi())
			{
				_interactiveUi.push_back(_uiData);
			}
		}
		return _interactiveUi;
	}




public:
	void Update();
	void CloseAll();
	void CloseWithId(const vector<string>& _ids);
	void DisplayAllUi() const;
	bool Contain(const string& _id,const string& _value);

public:
	void Reset();
};

