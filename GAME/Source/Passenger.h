namespace game_framework
{
class Station;
class Passenger
{
    public:
        Passenger();
        Passenger(int, int, int, int, int);
        void LoadBitmap();									//載入圖形
        void SetType(int);
        void SetXY(int, int);
        void SetX(int n);
        void SetY(int n);
        void SetIsNight(bool);
        int GetStartStation();
        int GetFinalStation();
        int GetPassengerType();
        void RandomMadePassenger(vector<Passenger*>& passengerList, vector<Station>& stationList, int stationMaxium, int stationTypeNum, int passenagerNum);
        void OnShow();										//將圖形貼到畫面
        void RandomOnePassenger(vector<Passenger*>& passengerList, vector<Station>& stationList, int stationMaxium, int stationTypeNum);
        ~Passenger();
    private:
        CMovingBitmap passengerAnimation;					//乘客圖形
        CMovingBitmap passengerAnimationNight;					//乘客圖形
        int finalStation;									//終點
        int startStation;									//起點
        int x, y;											//圖形座標
        int passengerType;									//乘客類型
        bool isNight = false;
        //乘客在車廂的位置
        const int PASSENGERPOSITIONX_UPDOWN[6] = { 2, 16, 2, 16, 2, 16 };
        const int PASSENGERPOSITIONY_UPDOWN[6] = { 2, 2, 16, 16, 30, 30 };
        const int PASSENGERPOSITIONX_RIGHTLEFT[6] = { 2, 2, 16, 16, 30, 30 };
        const int PASSENGERPOSITIONY_RIGHTLEFT[6] = { 2, 16, 2, 16, 2, 16 };
        //乘客在車站的位置
        const int PASSENAGE_POSITION[10] = { 25, 36, 47, 58, 69, 80, 91, 102, 113, 124 };
};
}

