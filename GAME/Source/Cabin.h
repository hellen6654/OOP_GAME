
namespace game_framework
{
	class Passenger;
	class Cabin
	{
	public:
		Cabin();
		~Cabin();
		void SetXY(int, int);
		void SetVelocity(int);
		void SetDirection(char);
		int  GetX();
		int  GetY();
		int  GetVelocity();
		void OnMove();
		void OnShow();
	private:
		CMovingBitmap cabinAnimation;	//車廂大小 42*28 每個乘客的邊緣各2px
		char direction;					//車廂朝哪個方向移動
		int x, y;						//車廂的左上角位置
		int velocity;					//速度
		int head;						//頭的座標在哪邊
		bool isTurn;					//車廂是轉彎的狀態嗎
		int color[3];					//車廂顏色
		int nextStation;
		int passedStation;
		//int passenagerNum; //最多六個
		//vector<Passenger*> passengerList;
		
	};
}


