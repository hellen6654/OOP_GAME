
namespace game_framework
{
	
	class Cabin
	{
	public:
		Cabin();
		Cabin(int,int,int,int,int);
		~Cabin();
		void SetXY(int, int);
		void SetVelocity(int);
		void SetMovingCabin(string,int);
		void SetIsShow(bool);
		void SetRGB(int, int, int);
		void SetGoingDirection(string);
		void SetMovingDirection(string);
		void SetLinePoint(vector<int>, vector<int>);
		int  GetX();
		int  GetY();
		int  GetVelocity();
		bool IsShow();
		void OnMove();
		void OnShow();
	private:
		//車廂大小 42*28 每個乘客的邊緣各2px
		int nextPoint=1;
		int prePoint=0;
		string movingDirection = "";
		string goingDirection="";
		int leftTopX, leftTopY;			//車廂的左上角位置
		int rightDownX, rightDownY;		//車廂的右下角位置
		int velocity;					//速度
		int color[3];					//車廂顏色
		bool isShow;
		vector<int> linePointX;
		vector<int> linePointY;
		//int passenagerNum; //最多六個
		//vector<Passenger*> passengerList;
		
	};
}


