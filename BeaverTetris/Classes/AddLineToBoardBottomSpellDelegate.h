#pragma once
class AddLineToBoardBottomSpellDelegate
{
public:
	AddLineToBoardBottomSpellDelegate(void);
	virtual ~AddLineToBoardBottomSpellDelegate(void);

	virtual void upGameBoard() = 0;
	virtual void addLineToGameBoard() = 0;

};

