
namespace game_framework
{
class Passenger
{
    public:
        Passenger();
        Passenger(int, int, int);
        void LoadBitmap();			//載入圖形
        void SetXY(int, int);		//設定座標
        int GetX();
        int GetY();
        void SetType(int);
        void RandomBuildPassenger(vector<Passenger>&, int, int, int, int);
        void OnShow();				//將圖形貼到畫面
        ~Passenger();
    private:
        const int MAXIUM_PASSENGER = 10;					//會出現在地圖上的只有10個乘客
        const int MAXIUM_PASSENGER_TYPE = 7;				//乘客樣式總共有7個 00~06
        const int MAX_GAME_MAP_SIDE_X = 770;			//實際上的遊戲邊界X軸只有到770
        const int MIN_GAME_MAP_SIDE_X = 30;			    //實際上的遊戲邊界X軸從30開始
        const int MAX_GAME_MAP_SIDE_Y = 570;			//實際上的遊戲邊界Y軸只有到570
        const int MIN_GAME_MAP_SIDE_Y = 60;			    //實際上的遊戲邊界Y軸從60開始
        int x, y;										//圖形座標
        int passengerType;								//乘客類型
        CMovingBitmap passengerAnimation;					//利用動畫作圖形



};
}



