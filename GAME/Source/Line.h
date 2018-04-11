
namespace game_framework
{
	class Line
	{
	public:
		Line();
		~Line();
		void DrawRailway(int,int,int,int);
		bool IsClickedStation(int, int, vector<Station>, int);
		bool IsClickedTwoStation();
		int  GetclickedTwoNumA();
		int  GetclickedTwoNumB();
		void SetclickedTwoNumA(int);
		void SetclickedTwoNumB(int);
	private:
		int clickedStationNumA;
		int clickedStationNumB;
	};

	
}