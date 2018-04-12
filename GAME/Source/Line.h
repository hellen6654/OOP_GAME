
namespace game_framework
{
	class Line
	{
	public:
		Line();
		
		~Line();
		void SetLineColor(int,int,int);
		void DrawRailway(int, int, int, int);
		bool IsClickedStation(int, int, vector<Station>, int);
		bool IsClickedTwoStation();
		int  GetclickedTwoNumA();
		int  GetclickedTwoNumB();
		int  GetLineColor();
		void SetclickedTwoNumA(int);
		void SetclickedTwoNumB(int);
		bool IsMouseClickedBMP(int,int);
		void LoadBitmap();
		void ShowBitmap();
	private:
		CMovingBitmap lineColorBMP;
		int clickedStationNumA;
		int clickedStationNumB;
		int lineColor[3];
		//red(255.0.0),orang(255.144.0),yellow(255.255.0),green(0.255.0),blue(0.138.255),bblue(0.6.255),puple(144.0.255)
	};

	
}