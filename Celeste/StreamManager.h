#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include <vector>
#include "Singleton.h"


using namespace std;

class StreamManager : public Singleton<StreamManager>
{
	bool SaveValue(const string& _value, const string& _path, int _defaultCount = 1) {
		ifstream _inFile(_path);
		ofstream _tempFile("temp.txt");

		if (!_inFile || !_tempFile) {
			cerr << "Erreur => le flux n'a pas été correctement construit ! : SaveValue" << endl;
			return false;
		}

		const string& _nameToFind = _value;
		string _line;
		bool _found = false;

		while (getline(_inFile, _line)) {
			size_t _pos = _line.rfind(_nameToFind + " x");
			if (_pos != string::npos) {
				// Si la valeur avec un suffixe 'x' est trouvée, extraire le nombre
				int _count = stoi(_line.substr(_pos + _nameToFind.length() + 2));
				_tempFile << _line.substr(0, _pos) << _nameToFind << " x" << to_string(_count + _defaultCount) << endl;
				_found = true;
			}
			else if (_line == _nameToFind) {
				// Si la valeur est trouvée sans le suffixe 'x', ajouter " x1"
				_found = true;
				_tempFile << _line << " x" + to_string(_defaultCount) << endl;
			}
			else {
				_tempFile << _line << endl;
			}
		}

		// Si la valeur n'a pas été trouvée, ajouter avec le suffixe 'x1'
		if (!_found) {
			_tempFile << _value << " x" + to_string(_defaultCount) << endl;
		}

		_inFile.close();
		_tempFile.close();

		const char* _cPath = _path.c_str();
		remove(_cPath);
		rename("temp.txt", _cPath);

		return true;
	}

	bool SaveMap(ofstream& _stream, const vector<vector<string>>& _map) {

		string _line;
		for (const vector<string>& _valueLine : _map) {
			for (const string& _value : _valueLine) {
				_stream << _value;
			}
			_stream << endl;
		}
		_stream.close();
		return true;
	}

public:
	/// <summary>
	/// Save un vector de vector de string dans un fichier .TXT a l'aide d'un path
	/// </summary>
	/// <param name="_array"></param>
	/// <param name="_path"></param>
	/// <returns></returns>
	bool SaveMap(const vector<vector<string>>& _array, const string& _path) {
		ofstream _stream(_path);
		if (!_stream) {
			cerr << "Erreur => le flux n'a pas ete correctement construit ! : SaveMap" << endl;
			return false;
		}

		if (!SaveMap(_stream, _array)) return false;

		return true;
	}


	/// <summary>
	/// Save les valeurs dans un fichier .TXT a partir d'un vecteur de string et du path du fichier
	/// </summary>
	/// <param name="_array"></param>
	/// <param name="_path"></param>
	/// <returns></returns>
	bool SaveValuesWithCount(vector<string>& _array, const string& _path) {

		for (const string& _value : _array) {
			if (!SaveValue(_value, _path)) return false;
		}

		return true;
	}

	/// <summary>
	/// Save une valeur dans un fichier .TXT a partir d'un string et du path du fichier
	/// </summary>
	/// <param name="_array"></param>
	/// <param name="_path"></param>
	/// <returns></returns>
	bool SaveValueWithCount(const string& _value, const string& _path, int _defaultCount = 1) {

		if (!SaveValue(_value, _path, _defaultCount)) return false;
		return true;
	}

	/// <summary>
	/// Load un fichier .TXT dans un vector de string a l'aide d'un path
	/// </summary>
	/// <param name="_array"></param>
	/// <param name="_path"></param>
	/// <returns></returns>
	bool Load(vector<string>& _array, const string& _path) {
		ifstream _stream = ifstream(_path);
		if (!_stream) {
			cerr << "Erreur => le flux n'a pas ete correctement construit ! : Load" << endl;
			_array = vector<string>();
			return false;
		}
		_array.clear();
		string _line;
		while (getline(_stream, _line)) {
			_array.push_back(_line);
		}
		return true;
	}

	/// <summary>
	/// Load un fichier .TXT dans un vector de vector de char a l'aide d'un path
	/// </summary>
	/// <param name="_array"></param>
	/// <param name="_path"></param>
	/// <returns></returns>
	bool LoadSmallMap(vector<vector<char>>& _array, const string& _path) {

		ifstream _stream = ifstream(_path);
		if (!_stream) {
			cerr << "Erreur => le flux n'a pas ete correctement construit ! : LoadSmallMap" << endl;
			_array = vector<vector<char>>();
			return false;
		}
		_array.clear();
		vector<char> _newArray;
		char _char;
		while (_stream.get(_char)) {

			_newArray.push_back(_char);
		}
		_array.push_back(_newArray);
		return true;
	}


	/// <summary>
	/// Load les int qui sont séparer par un '.' d'un fichier .TXT dans un vector de vector de int a l'aide d'un path
	/// </summary>
	/// <param name="_array"></param>
	/// <param name="_path"></param>
	/// <returns></returns>
	bool LoadMapLevel(vector<vector<int>>& _array, const string& _path) {
		ifstream _stream = ifstream(_path);
		if (!_stream) {
			cerr << "Erreur => le flux n'a pas ete correctement construit ! : LoadMap" << endl;
			_array = vector<vector<int>>();
			return false;
		}
		_array.clear();
		string _line;
		int _index = 0;
		while (getline(_stream, _line)) {
			vector<int> _numbersLines;

			size_t _firstPos = 0;
			size_t _endPos = 0;

			while (_endPos < _line.size()) {
				_firstPos = _line.find_first_of("0123456789", _endPos);
				_endPos = _line.find_first_not_of("0123456789", _firstPos);

				if (_firstPos != string::npos) {
					string numberStr = _line.substr(_firstPos, _endPos - _firstPos);
					int _number = stoi(numberStr);
					_numbersLines.push_back(_number);
				}
			}
			_array.push_back(_numbersLines);
		}
		_stream.close();
		return true;
	}
};