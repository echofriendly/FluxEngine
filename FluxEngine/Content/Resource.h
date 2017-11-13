#pragma once

class Resource
{
public:
	Resource();
	~Resource();

	DELETE_COPY(Resource)

	virtual bool Load(const std::string& filePath) = 0;
	virtual bool Save(const std::string& filePath);

	void SetName(const std::string& name) { m_Name = name; }
	const std::string& GetName() { return m_Name; }

protected:
	string m_Name;
};