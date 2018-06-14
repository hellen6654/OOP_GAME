
namespace game_framework
{
	class Passenger;
	class Station
	{
	public:
		Station();
		Station(int, int, int);
		void LoadBitmap();			//載入圖形
		void SetXY(int, int);		//設定座標
		void SetPassenagerNum(int); //設定目前乘客數量
		void SetAddPassenagerNum(int); //設定增加目前乘客數量
		int GetX();
		int GetY();
		int GetCenterPositionX();
		int GetCenterPositionY();
		int GetPassenagerNum();
		void SetType(int);
		void RandomBuildStation(vector<Station>&);
		void CheckedOverLappingStation(vector<Station>&);
		void SetPassengerToStationPosition(Passenger* p);
		void ErasePassenger(Passenger* p);
		void OnShowStation();				//將圖形貼到畫面
		void OnShowPassengerInStation();
		~Station();
	private:
		const int MAXIUM_STATION = 6;					//會出現在地圖上的只有6個車站
		const int MAXIUM_STATION_TYPE = 6;				//車站樣式總共有6個 00~05
		//mygame.h 裡面也有相同的屬性要改
		const int MAX_GAME_MAP_SIDE_X = 770-135;			//實際上的遊戲邊界X軸只有到770 
		const int MIN_GAME_MAP_SIDE_X = 30;			    //實際上的遊戲邊界X軸從30開始
		const int MAX_GAME_MAP_SIDE_Y = 560-25;		//實際上的遊戲邊界Y軸只有到560
		const int MIN_GAME_MAP_SIDE_Y = 60;			    //實際上的遊戲邊界Y軸從60開始
		const int PASSENAGE_POSITION[10] = {25,36,47,58,69,80,91,102,113,124};
		const int centerPositionX;						//中心X座標
		const int centerPositionY;						//中心Y座標
		int x, y;										//圖形座標
		int stationType;								//車站類型
		int passenagerNum;								//總共有幾個乘客在車站

		CMovingBitmap stationAnimation;					//利用動畫作圖形
		vector<Passenger*> passengerInStationList;		//在車站的乘客
	};
}


