
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
		void SetLinePointXY(vector<Station>);							//設定轉折點的XY座標

		int  GetClickedStartStationNum();								//取得ClickedStartStationNum
		int  GetClickedEndStationNum();									//取得ClickedEndStationNum
		int  GetMouseClickedStationNum(int,int,vector<Station>,int);	//取得滑鼠點到的那個車站的編號
		void GetLineColorRGB(int& R, int& G, int& B);					//取得線路顏色RGB
		int  GetLineColor();											//取得線路顏色編號 red=0 orange=1 ....
		int  GetClickedFirstStation();									//取得線路車站起點
		int  GetClickedLastStation();									//取得線路車站終點
		void GetLinePointXY(vector<int>&,vector<int>&);
		void GetPassedStationNum(vector<int>&);
		void GetTotalPassedStation(int(&num)[6]);
		void Reset();

		bool IsClickedStation(int, int, vector<Station>, int);			//檢查是否點到車站 有就回傳ture 如果沒有則回傳false
		bool IsClickedTwoStation();										//檢查是否已經點了兩個車站了

		bool IsMouseClickedLineColorBMP(int,int);						//檢查是否滑鼠有點到下方線路顏色的圖片 //換線路顏色要用的啦
		bool IsPassedStationEmpty();									//檢查是否有在地圖上拉出線路了
		void CountTotalPassedStation();									//計算線路所經過的車站類型
		void LoadBitmap();						
		void ShowLineIconBitmap();										//顯示畫面底部的的圖片icon
		void ShowRailway(vector<Station>);								//劃出線路
		bool IsIconCanBeClicked();
		void SetIsCanbeClicked(bool b);
		bool IsClicked();
		void SetIsClicked(bool b);
	private:
		CMovingBitmap lineColorBMP;
		int clickedStartStationNum;
		int clickedEndStationNum;
		int lineColor[3];
		bool isCanBeClicked;
		bool isClicked = false;
		int totalPassedStationNum[6] = {0};							//線路所經過的車站類型
		vector<int> passedStation;									//經過的車站的編號
		vector<int> linePointX;										//劃出線路點的X座標 與lineYPoint連動
		vector<int> linePointY;										//劃出線路點的Y座標 與lineXPoint連動
		//red(255.0.0),orang(255.144.0),yellow(255.255.0),green(0.255.0),blue(0.138.255),bblue(0.6.255),puple(144.0.255)
	};

	
}