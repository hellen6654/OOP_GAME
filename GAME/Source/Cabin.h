
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
		CMovingBitmap cabinAnimation;	//���[�j�p 42*28 �C�ӭ��Ȫ���t�U2px
		char direction;					//���[�­��Ӥ�V����
		int x, y;						//���[�����W����m
		int velocity;					//�t��
		int head;						//�Y���y�Цb����
		bool isTurn;					//���[�O���s�����A��
		int color[3];					//���[�C��
		int nextStation;
		int passedStation;
		//int passenagerNum; //�̦h����
		//vector<Passenger*> passengerList;
		
	};
}


