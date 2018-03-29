
namespace game_framework
{
	class Station
	{
	public:
		Station();
		Station(int,int,int);
		void LoadBitmap();			//載入圖形
		void SetXY(int, int);		//設定座標
		int GetX();
		int GetY();
		void SetType(int);
		void OnShow();				//將圖形貼到畫面
		~Station();
	private:
		int x, y;					//圖形座標
		int station_type;			//車站類型
		CMovingBitmap station_animation;	//利用動畫作圖形
	};
}


