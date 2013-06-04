#pragma once

class EquipmentVisitor;

class Equipment
{
public:
	virtual ~Equipment(void);
	
	const char* Name()
	{
		return m_name;
	}

	virtual void Accept(EquipmentVisitor* equipVisitor);

protected:
	Equipment(void);
private:
	const char* m_name;
};
