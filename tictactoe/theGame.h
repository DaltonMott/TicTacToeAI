	struct GameInfo {

	char square[10];
	bool win;
	bool OStart;
	bool hard;
	int turnCounter;
	int playerPosition[5];
	int priority;
	const char playerMark;
	const char OMark;
} gameInfo;	

	void waitFor(unsigned int str);
	bool whoFirst();
	bool difficulty();
	void rules(struct GameInfo* gameInfo);
	void drawBoard(struct GameInfo* gameInfo);
	bool checkEnd(struct GameInfo* gameInfo);
	int getch (void);
	void playersTurn(struct GameInfo* gameInfo);
	void theGamesTurn(struct GameInfo* gameInfo);
	bool taken(struct GameInfo* gameInfo, int i);
	bool nearWin(struct GameInfo* gameInfo, char mark);
	
