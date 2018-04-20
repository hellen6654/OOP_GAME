
namespace game_framework
{
	class Line
	{
	public:
		Line();	
		~Line();
		
		void DrawRailway(int, int, int, int);							//畫 出軌 道

		void SetLineColor(int,int,int);									//設定線路顏色
		void SetClickedStartStationNum(int);							//設定ClickedStartStationNum
		void SetClickedEndStationNum(int);								//設定ClickedEndStationNum
		void SetPassedStation(int,int);									//設定有經過的車站

		int  GetClickedStartStationNum();								//取得ClickedStartStationNum
		int  GetClickedEndStationNum();									//取得ClickedEndStationNum
		int  GetMouseClickedStationNum(int,int,vector<Station>,int);	//取得滑鼠點到的那個車站的編號
		int  GetLineColorNum();											//取得線路顏色編號 red=0 orange=1 ....
		int  GetClickedFirstStation();									//取得線路車站起點
		int  GetClickedLastStation();									//取得線路車站終點

		bool IsClickedStation(int, int, vector<Station>, int);			//檢查是否點到車站 有就回傳ture 如果沒有則回傳false
		bool IsClickedTwoStation();										//檢查是否已經點了兩個車站了
		bool IsMouseClickedLineColorBMP(int,int);						//檢查是否滑鼠有點到下方線路顏色的圖片 //換線路顏色要用的啦
		bool IsPassedStationEmpty();
		

		void LoadBitmap();
		void ShowLineIconBitmap();
		void ShowRailway(vector<Station>,int);							//劃出路線
	private:
		CMovingBitmap lineColorBMP;
		int clickedStartStationNum;
		int clickedEndStationNum;
		int lineColor[3];
		vector<int> passedStation;
		//red(255.0.0),orang(255.144.0),yellow(255.255.0),green(0.255.0),blue(0.138.255),bblue(0.6.255),puple(144.0.255)
	};

	
}