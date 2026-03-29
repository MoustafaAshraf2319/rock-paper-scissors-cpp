#include <iostream>
using namespace std;
enum enGameChoice { Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };
struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};
struct stGameResults
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTime = 0;
	enWinner GameWinner;
	string WinnerName = "";
};
int RandomNumber(int From, int To)
{
	int RandomNumber = rand() % (To - From + 1) + From;
	return RandomNumber;
}
string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1","Computer","No Winner" };
	return arrWinnerName[Winner - 1];
}
string ChoiceName(enGameChoice GameChoice)
{
	string arrGameChoices[3] = { "Rock","Paper","Scissors" };
	return arrGameChoices[GameChoice - 1];
}
enGameChoice ReadPlayerChoice()
{
	short Choice = 1;
	do
	{
		cout << "\nYour Choice: [1]:Rock, [2]:Paper, [3]:Scissors? ";
		cin >> Choice;
	} while (Choice < 1 || Choice >3);
	return (enGameChoice)Choice;
}
enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}
	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Rock:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Rock)
		{
			return enWinner::Computer;
		}
		break;
	}
	return enWinner::Player1;
}
void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 2F");
		break;
	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;
	case enWinner::Draw:
		system("color 6F");
		break;
	}
}

string Tabs(short NumberOfTabs)
{
	string t = "";
	for (int i = 0; i < NumberOfTabs; i++)
	{
		t += "\t";
		cout << t;
	}
	return t;
}
void PrintRoundResult(stRoundInfo RoundInfo)
{
	cout << endl << Tabs(2) << "-------------- Round [" << RoundInfo.RoundNumber << "]-----------------\n";
	cout << Tabs(1) << "Player1Choice     : " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << Tabs(1) << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << Tabs(1) << "Round Winner    : [" << RoundInfo.WinnerName << "] \n";
	cout << Tabs(1) << "--------------------------------------\n";
	SetWinnerScreenColor(RoundInfo.Winner);
}
enWinner WhoWonTheGame(short Player1Win, short ComputerWinTime)
{
	if (Player1Win > ComputerWinTime)
		return enWinner::Player1;
	else if (ComputerWinTime > Player1Win)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";

		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player1)
			PlayerWinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResult(RoundInfo);
	}

	stGameResults GameResults;

	GameResults.GameRounds = HowManyRounds;
	GameResults.Player1WinTimes = PlayerWinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTime = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;
}

void ShowGameOverScreen()
{
	cout << Tabs(1) << "------------------------------------------------------\n";
	cout << Tabs(1) << "                      +++ G A M E  O V E R +++                          \n";
	cout << Tabs(1) << "-------------------------------------------------------\n";
}
void ShowFinalGameResults(stGameResults GameResults)
{
	cout << Tabs(1) << "_____________________ [Game Results]_____________________\n\n";
	cout << Tabs(1) << "Game Rounds : " << GameResults.GameRounds << endl;
	cout << Tabs(1) << "Player1 won times : " << GameResults.Player1WinTimes << endl;
	cout << Tabs(1) << "Computer won times : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(1) << "Draw times : " << GameResults.DrawTime << endl;
	cout << Tabs(1) << "Final Winner : " << GameResults.WinnerName << endl;
	cout << Tabs(1) << "___________________________________________________________\n";
	SetWinnerScreenColor(GameResults.GameWinner);
}
short ReadHowManyRounds()
{
	short GameRound = 0;
	do
	{
		cout << " How many rounds from 1 to 10 \n";
		cin >> GameRound;
	} while (GameRound < 1 || GameRound>10);
	return GameRound;
}
void ResetScreen()
{
	system("color 0F");
	system("cls");
}
void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << endl << Tabs(3) << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}

